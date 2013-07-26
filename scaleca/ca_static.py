"""ca_static.py - a simple static CA for testing.

Demonstrates the methods a CA needs to implement."""

import numpy as np

class CA(object):

    def __init__(self, max_row, max_col):
        self.array = np.zeros((max_row, max_col), dtype=np.uint8)
        self.array[2:5,3:8] = 1

    def update(self):
        pass

    def get_state_as_string(self):
        max_row, max_col = self.array.shape
        str_array = ''.join([str(i) for i in self.array.reshape((1, -1))[0]])
        return '%d,%d:%s' % (max_row, max_col, str_array)

