"""ca_static.py - a simple static CA for testing.

Demonstrates the methods a CA needs to implement."""

import numpy as np
from ca_base import CABase

class CA(CABase):

    def __init__(self, max_row, max_col):
        self.array = np.zeros((max_row, max_col), dtype=np.uint8)
        self.array[2:5,3:8] = 1

    def update(self):
        pass


