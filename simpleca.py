#!/usr/bin/env python
"""simpleca.py - A simple prototype CA program in python."""

import numpy
import random
from matplotlib import pyplot as plt

def display_ca(ca):
    plt.imshow(test_ca, interpolation='nearest')
    plt.show()

def random_ca(nrows, ncols):
    base_array = numpy.random.randint(2, size=nrows * ncols)

    return numpy.reshape(base_array, (nrows, ncols))


test_ca = random_ca(100, 100)
display_ca(test_ca)
