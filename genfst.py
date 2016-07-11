import sys

# Dependency FAdo

from FAdo import fa
sys.path.append('py-fst')
import fio
from FAdo import fl
from FAdo import rndfap
from FAdo import transducers as t
from numpy import random as rand
import numpy as np
import random


(n,k,sout,N) = [int(x) for x in sys.argv[1:]]

# random.seed(init)
# n - number of states
# n - size of (input) alphabet
# sout - size of (output) alphabet
# N - number of transducers produced

randfa = rndfap.ICDFArnd(n,k)

for i in range(N):

    fa = randfa.next()

    fa = fa.toNFA()

    #Standard Form transducers
    tr = t.SFT()

    tr.Sigma = fa.Sigma
    tr.States = fa.States
    tr.Initial = fa.Initial
    # tr.Final = fa.Final
    tr.Final = fa.States #So that all inputs are accepted.
    transitions = fa.delta
    for state in transitions:
        for input in transitions[state]:
            (outstate,) = transitions[state][input]
            tr.addTransition(state, input, str(rand.randint(0, sout)), outstate)

    # print "tr.Sigma", tr.Sigma
    # print "tr.States", tr.States
    # print "tr.Initial", tr.Initial
    # print "tr.Final", tr.Final
    # print "tr.delta", tr.delta

    filename = "fst/"+str(i)

    test = fio.saveToFile(filename,tr,'w+')

    # print test

    # print tr
    # tr.display()
