import FAdo
from FAdo import fa
from FAdo import fl
from FAdo import rndfap
from FAdo import transducers as t
from numpy import random as rand
import numpy as np

rand.seed(0)

n = 5 #number of states
k = 2 #size of (input) alphabet
s = 2 #size of (output) alphabet
randfa = rndfap.ICDFArnd(n,k)

faa = randfa.next()

from sage.combinat.finite_state_machine import FSMState

F = Transducer(faa.delta)
