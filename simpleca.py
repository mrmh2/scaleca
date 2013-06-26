#!/usr/bin/env python
"""simpleca.py - A simple prototype CA program in python."""

import numpy as np
import random
from matplotlib import pyplot as plt

def display_ca(ca):
    plt.imshow(ca, interpolation='nearest')
    plt.show()

def random_ca(nrows, ncols):
    base_array = np.random.randint(2, size=nrows * ncols)

    return np.reshape(base_array, (nrows, ncols))

def tl_ca(nrows, ncols):
    ca = np.zeros((nrows, ncols))
    ca[50, 50] = 1
    ca[50, 49] = 1
    ca[50, 51] = 1

    return ca

def make_update_rule():
    n = [-1, 0, 1]
    ln = [(r, c) for r in n for c in n]
    ln.remove((0, 0))

    update_rule_l = {s: 0 for s in range(0, 9)}
    update_rule_l[2] = 1
    update_rule_l[3] = 1

    def ur(ca, location):
        r, c = location
        nvals = [ca[r+ro, c+co] for ro, co in ln]
        nsum = sum(nvals)
        if ca[r, c] == 1:
            return update_rule_l[nsum]
        else:
            new_val = 1 if nsum == 3 else 0
            return new_val

    return ur

def next_generation(ca, update_rule):
    nrows, ncols = ca.shape
    ng = np.zeros((nrows, ncols))

    for r in range(1, nrows-1):
        for c in range(1, ncols-1):
            ng[r, c] = update_rule(ca, (r, c))

    return ng


#test_ca = random_ca(100, 100)
test_ca = tl_ca(100, 100)
ng = next_generation(test_ca, make_update_rule())
display_ca(test_ca)
display_ca(ng)
