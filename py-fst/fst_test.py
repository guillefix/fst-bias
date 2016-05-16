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
from scipy import stats

import matplotlib.pyplot as plt

init = 3568
Nmax = 100
nbits = 34
step = 100
Nin = 2**nbits
Nsample = 3000

frequency = Counter({})
probustness = Counter({})
pevol = Counter({})
unbias = []
frcomp = []
pvals = []

random.seed(init)
n = 4 #number of states
k = 2 #size of (input) alphabet
sout = 2 #size of (output) alphabet
randfa = rndfap.ICDFArnd(n,k)

def runFST(word, nbits, tr):
    faa = tr.runOnWord(word)
    # print inputstr
    faa.addFinal(len(faa.States)-1)
    output = faa.enumNFA(nbits)
    outputstr = output[0]
    return outputstr

rand.seed(init)

for s in range(init,init+Nmax):

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
    temp_freq = Counter({})
    grobustness = Counter({})
    temp_pros = Counter({})
    pneigh = {}
    entropy = 0
    comptemp = []
    logfreqarray = []
    #range(0, Nin, step):
    random.seed()
    for x in np.nditer(rand.randint(0,Nin, Nsample)):
        inputstr = bin(x.item(0))
        inputstr = inputstr[2:]
        inputstr = inputstr.zfill(nbits)
        outputstr = runFST(inputstr,nbits,tr);
        temp_freq[outputstr] += 1

        # for y in range(0,len(inputstr)-1):
        #     inputstr2 = inputstr
        #     inputstr2 = list(inputstr2)
        #     if inputstr2[y] == '1':
        #         inputstr2[y] = '0'
        #     elif inputstr2[y] == '0':
        #         inputstr2[y] = '1'
        #     inputstr2 = "".join(inputstr2)
        #     outputstr2 = runFST(inputstr2,nbits,tr)
        #     if outputstr2 == outputstr:
        #         grobustness[inputstr] += 1
        # probustness[outputstr] += grobustness[inputstr]

    # Below is for looking only at transducers with a minimum bias

    # print frTempSorted[0][1]
    Nout = len(temp_freq)
    frTempSorted = temp_freq.most_common(Nout)
    # if frTempSorted[0][1] > 1*frTempSorted[len(temp_freq)-1][1]:
    #     for x in range(0, 2**nbits, step):
    #         inputstr = bin(x)
    #         inputstr = inputstr[2:]
    #         inputstr = inputstr.zfill(nbits)
    #         outputstr = runFST(inputstr,nbits,tr);
    #         pneigh[outputstr] = []
    #         # frequency[outputstr] += 1
    #
    #         for y in range(0,len(inputstr)-1):
    #             inputstr2 = inputstr
    #             inputstr2 = list(inputstr2)
    #             if inputstr2[y] == '1':
    #                 inputstr2[y] = '0'
    #             elif inputstr2[y] == '0':
    #                 inputstr2[y] = '1'
    #             inputstr2 = "".join(inputstr2)
    #             outputstr2 = runFST(inputstr2,nbits,tr)
    #             if outputstr2 == outputstr:
    #                 grobustness[inputstr] += 1
    #             elif outputstr2 not in pneigh[outputstr] :
    #                 pevol[outputstr] += 1
    #                 pneigh[outputstr].append(outputstr2)
    #         temp_pros[outputstr] += grobustness[inputstr]
        # for seq in frTempSorted: # could do it temp_freq too
        #     frequency[seq[0]] += seq[1]
            # probustness[seq[0]] += float(temp_pros[seq[0]])/temp_freq[seq[0]]
        # stats.pearsonr(frTempSorted.values(), )
    for seq in frTempSorted: # could do it temp_freq too
        frequency[seq[0]] += seq[1]
        entropy -= (float(seq[1])/Nsample)*np.log(float(seq[1])/Nsample)/np.log(2)
        # probustness[seq[0]] += float(temp_pros[seq[0]])/temp_freq[seq[0]]
    unbias.append((2**entropy)/Nout)
    for seq in frTempSorted:
        logfreqarray.append(np.log(float(seq[1]))/np.log(2))
        compstr = zlib.compress(seq[0], 9)
        comptemp.append(len(compstr))
    frcomp.append(stats.pearsonr(comptemp, logfreqarray)[0]) #assumes gaussian...
    pvals.append(stats.pearsonr(comptemp, logfreqarray)[1])
    print s

frSorted = frequency.most_common(len(frequency))
print frSorted
outfile = open('frSorted', 'w')
pickle.dump(frSorted, outfile)
freqAvs = []
pRobAvs = []
pevolAvs = []
complexities = []
for seq in frSorted:
    freqAvs.append(float(seq[1])/Nmax)
    # if frequency[seq[0]] == 0: #I guess just to make sure..
    #     pRob = 0
    # else:
    #     pRob = probustness[seq[0]]/Nmax
    # pRobAvs.append(pRob)
    # pevolAvs.append(float(pevol[seq[0]])/Nmax)
    compstr = zlib.compress(seq[0], 9)
    complexities.append(len(compstr))
print freqAvs
outfile = open('freqAvs', 'w')
pickle.dump(freqAvs, outfile)

print sum(unbias)/len(unbias)

print sum(frcomp)/len(frcomp)

print sum(pvals)/len(pvals)

# plot the freq vs complexity graph

plt.plot(complexities,freqAvs, 'o')
plt.ylabel('Average frequency')
plt.yscale('log')
plt.xlabel('complexity')
plt.show()

# plot the freq vs robsutness graph

# plt.plot(freqAvs,pRobAvs, 'o')
# plt.ylabel('Average robustness')
# plt.yscale('log')
# plt.xlabel('Average frequency')
# plt.xscale('log')
# plt.show()

# plot the freq vs robsutness graph

# plt.plot(pRobAvs,pevolAvs, 'o')
# plt.xlabel('Average robustness')
# plt.ylabel('Average evolvability')
# plt.show()
