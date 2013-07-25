"""CA engine"""

import random
import numpy as np
import pickle

import scipy.misc

class CA(object):

    def __init__(self, array):
        self.array = array

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
        max_x, max_y = self.array.shape
        next_state = np.zeros((max_x, max_y), np.uint8)

        update_rule_l = {s: 0 for s in range(0, 10)}
        update_rule_l.update({s: 1 for s in range(5, 10)})
        #update_rule_l[4] = 0
        #update_rule_l[5] = 1

        all_cells = [(r, c) for r in range(1, max_y-1)
               for c in range(1, max_x-1)]

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
