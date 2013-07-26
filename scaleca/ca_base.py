"""ca_base - base CA class"""

class CABase(object):

    def get_state_as_string(self):
        max_row, max_col = self.array.shape
        str_array = ''.join([str(i) for i in self.array.reshape((1, -1))[0]])
        return '%d,%d:%s' % (max_row, max_col, str_array)
