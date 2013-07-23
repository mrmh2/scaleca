"""CA engine"""

import numpy as np

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

    def update(self):
#        print 'up'
#        print self.array
 #       print self.nn(9, 11)
        
        ln = [-1, 0, 1]
        h8 = [(r, c) for r in ln for c in ln]
        h8.remove((0, 0))
        #print h8
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
 #       print self.array


        # print 'nn', self.nn(10, 10)
        # ar, ac = 10, 10
        # for r, c in h8:
        #     print ar+r, ac+c, self.array[ar+r, ac+c]
        
#        print [self.array[ar+r, ac+c] for r, c in h8]
