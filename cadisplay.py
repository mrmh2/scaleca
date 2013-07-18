"""CA display"""

class CARep(object):

    def __init__(self, array):
        self.array = array

class TextDisplay(object):

    def __init__(self, ca_rep):
        self.ca_rep = ca_rep

    def display(self):
        value_map = {0: '  ', 1: '**'}
        for row in self.ca_rep.array:
            print ''.join(value_map[c] for c in row)
