#!/usr/bin/env python
import sys

import numpy as np
#sys.path.insert(0, '../')
#from scaleca.ca_static import CA
from scaleca.ca_life import CA
from scaleca.disp_simple import CADisplay

def string_state_to_array(sstate, shape):
    c_sep = ','.join(sstate)
    one_d = np.fromstring(c_sep, dtype=np.uint8, sep=',')
    return one_d.reshape(shape)

def unpack_string_rep(sstate):
    dim, astring = sstate.split(':')
    shape = map(int, dim.split(','))
    astate = string_state_to_array(astring, shape)

    return astate

def get_state_maker(ca):
    def get_state():
        sstate = ca.get_state_as_string()
        astate = unpack_string_rep(sstate)
        ca.update()
        
        return astate

    return get_state
    
def main():
    test_ca = CA(10, 10)
    test_ca[5,5] = 1
    test_ca[5,4] = 1
    test_ca[5,6] = 1

    get_state = get_state_maker(test_ca)

    display = CADisplay()

    display.run_display(get_state)

if __name__ == '__main__':
    main()
