"""CA engine"""

import random
import numpy as np
import pickle

import scipy.misc

from ca_base import CABase

class CA(CABase):

    def __init__(self, max_row, max_col):
        self.max_row = max_row
        self.max_col = max_col
        
        self.array = np.zeros((max_row, max_col), dtype=np.uint8)

    def __setitem__(self, key, value):
        self.array[key] = value

    def nn(self, ri, ci):
        ln = [-1, 0, 1]
        h8 = [(r, c) for r in ln for c in ln]
        h8.remove((0, 0))
        nn = sum([self.array[ri+r, ci+c] for r, c in h8])
        return nn

    def fill_random(self):
        xdim, ydim = self.array.shape

        for x in range(0, xdim):
            for y in range(0, ydim):
                self.array[x, y] = random.randint(0, 1)

    def sparse_rep(self):
        """Sparse representation of internal array"""
        return zip(*np.where(self.array==1))

    def inflate_rep(sparse_rep):
        print sparse_rep

    def save_state(self, filename):
        
        with open(filename, 'wb') as f:
            pickle.dump(self.array.shape, f)
            pickle.dump(self.sparse_rep(), f)

    def save_as_png(self, filename):
        xdim, ydim = self.array.shape
        outarray = np.zeros((xdim, ydim, 3), dtype=np.uint8)
        on = np.where(self.array == 1)
        #outarray[zip(*on)] = (255, 255, 255)
        scipy.misc.imsave(filename, outarray)

    def load_state(self, filename):

        with open(filename, 'rb') as f:
            shape = pickle.load(f)
            new_array = np.zeros(shape, dtype=np.uint8)
            sparse_rep = pickle.load(f)
            new_array[zip(*sparse_rep)] = 1
            self.array = new_array

    def update_vote(self):
        ln = [-1, 0, 1]
        h8 = [(r, c) for r in ln for c in ln]
        h8.remove((0, 0))
        next_state = np.zeros((self.max_row, self.max_col), np.uint8)

        update_rule_l = {s: 0 for s in range(0, 10)}
        update_rule_l.update({s: 1 for s in range(5, 10)})
        update_rule_l[4] = 1
        update_rule_l[5] = 0

        # Copies for wrap boundary conditions
        self.array[0,:] = self.array[self.max_row-2, :]
        self.array[self.max_row-1,:] = self.array[1,:]
        self.array[:,0] = self.array[:, self.max_col-2]
        self.array[:, self.max_col-1] = self.array[:, 1]

        all_cells = [(r, c) for r in range(1, self.max_row-1)
               for c in range(1, self.max_col-1)]

        for ar, ac in all_cells:
            nn = sum([self.array[ar+r, ac+c] for r, c in h8])
            next_state[ar, ac] = update_rule_l[self.array[ar, ac] + nn]

        self.array = next_state
        
    def update(self):
        
        ln = [-1, 0, 1]
        h8 = [(r, c) for r in ln for c in ln]
        h8.remove((0, 0))
        max_x, max_y = self.array.shape
        next_state = np.zeros((max_x, max_y), np.uint8)

        update_rule_l = {s: 0 for s in range(0, 9)}
        update_rule_l[2] = 1
        update_rule_l[3] = 1

        # Copy for wrap boundary conditions

        all_cells = [(r, c) for r in range(1, max_y-1)
               for c in range(1, max_x-1)]

        for ar, ac in all_cells:
            nn = sum([self.array[ar+r, ac+c] for r, c in h8])
            #print nn
            if self.array[ar, ac] == 1:
                next_state[ar, ac] = update_rule_l[nn]
            else:
                next_state[ar, ac] = 1 if nn == 3 else 0

        self.array = next_state
        #print h8
 #       print self.array


        # print 'nn', self.nn(10, 10)
        # ar, ac = 10, 10
        # for r, c in h8:
        #     print ar+r, ac+c, self.array[ar+r, ac+c]
        
#        print [self.array[ar+r, ac+c] for r, c in h8]
