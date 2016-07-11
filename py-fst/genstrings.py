import sys
from numpy import random as rand


(n,Ni,N) = [int(x) for x in sys.argv[1:]]

# n input size
# Ni number of inputs
# N number of files

inputn = 2**n

for i in range(N):
    f = open('str/'+str(i), 'w+')
    for j in range(Ni):
        f.write(('{0:0'+str(n)+'b}').format(rand.randint(0,inputn))+"\n")
    f.close()
