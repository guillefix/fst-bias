#!~/Documents/SageMath -python

from FAdo import fa
from FAdo import fl
from FAdo import rndfap
from FAdo import transducers as t
from numpy import random as rand
import numpy as np
import random
from collections import Counter
import copy
import zlib
import pickle

import matplotlib.pyplot as plt

init = 62
Nmax = 4000
nbits = 10

frNew = Counter({})
frOld = Counter({})

random.seed(init)
n = 5 #number of states
k = 2 #size of (input) alphabet
sout = 2 #size of (output) alphabet
randfa = rndfap.ICDFArnd(n,k)

for s in range(init,init+Nmax):

    rand.seed(s)

    fa = randfa.next()
    fa = fa.toNFA()

    #Standard Form transducers
    tr = t.SFT()

    tr.Sigma = fa.Sigma
    tr.States = fa.States
    tr.Initial = fa.Initial
    tr.Final = fa.Final
    transitions = fa.delta
    for state in transitions:
        for input in transitions[state]:
            (outstate,) = transitions[state][input]
            tr.addTransition(state, input, str(rand.randint(0, sout)), outstate)

    # print tr
    # tr.display()

    for x in range(0, 2**nbits):
        inputstr = bin(x)
        inputstr = inputstr[2:]
        inputstr = inputstr.zfill(nbits)
        faa = tr.runOnWord(inputstr)
        # print inputstr
        faa.addFinal(len(faa.States)-1)
        output = faa.enumNFA(nbits)
        outputstr = output[0]
        frNew[outputstr] += 1
    print s
    # freqs = Counter({})
    # for y in range(0, 2**nbits):
    #     # word = "11011011011"
    #     word = bin(y)
    #     word = word[2:]
    #     word = word.zfill(nbits)
    #     ns = []
    #     for x in range(0, 2**nbits):
    #         inputstr = bin(x)
    #         inputstr = inputstr[2:]
    #         inputstr = inputstr.zfill(nbits)
    #         # print inputstr
    #         if tr.evalWordP((inputstr, word)):
    #             ns.append(inputstr)
    #     freqs[word] = len(ns)
    #
    # frNew = frOld + freqs
    # frOld = copy.deepcopy(frNew)
    # print frNew

# for key in frNew:
#     frNew[key] /= Nmax
frSorted = frNew.most_common(len(frNew))
print frSorted
outfile = open('frSorted', 'w')
pickle.dump(frSorted, outfile)
freqAvs = []
complexities = []
for seq in frSorted:
    freqAvs.append(seq[1])
    compstr = zlib.compress(seq[0], 9)
    complexities.append(len(compstr))
print freqAvs
outfile = open('freqAvs', 'w')
pickle.dump(freqAvs, outfile)
plt.plot(complexities,freqAvs, 'o')
plt.yscale('log')
plt.show()
# fig = plt.figure()
# ax = fig.add_subplot(2,1,1)
# line, = ax.plot(freqAvs, color='blue', lw=2)
# ax.set_yscale('log')
# fig.show()
