import sys
import numpy as np
from numpy import linalg as LA

(n,n2,N) = [int(x) for x in sys.argv[1:]]

#n - number of states
#N - number of fst
#n2 - input string size

f = open('fst/'+str(N), 'r')

A0 = np.zeros((n,n))
A1 = np.zeros((n,n))

i = 0

for line in f:
    edge = line.split(' ')
    if not i:
        initial = int(edge[0])
        i+=1
    if len(edge) == 4:
        if edge[3][:-1] == "1":
            A1[edge[0], edge[1]] += 1
        elif edge[3][:-1] == "0":
            A0[edge[0], edge[1]] += 1

# to improve this I'd like to read the final states

A = A0 + A1

numstr = np.int64(2**n2)

prod = np.zeros((n**2,n**2), dtype=np.int64)

for j in range(n2):
    prod += np.kron(LA.matrix_power(np.transpose(A), n2-(j+1)),LA.matrix_power(A, j))

G0 = np.zeros((n,n), dtype=np.int64)

for k in range(n):
    for l in range(n):
        G0 += prod[k*n:(k+1)*n,l*n:(l+1)*n]*A0[k,l]

num0s = G0.dot(np.ones((n,1)))

G1 = np.zeros((n,n), dtype=np.int64)

for k in range(n):
    for l in range(n):
        G1 += prod[k*n:(k+1)*n,l*n:(l+1)*n]*A1[k,l]

num1s = G1.dot(np.ones((n,1)))

print (num0s[initial]/(numstr))/n2
print (num1s[initial]/(numstr))/n2
print (num1s[initial]/(numstr))/n2 + (num0s[initial]/(numstr))/n2

paths = (LA.matrix_power(A,n2)).dot(np.ones((n,1)))
print paths[initial]/numstr
