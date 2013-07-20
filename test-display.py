#!/usr/bin/env python

import numpy as np
from ca_display import CARep, TextDisplay
from ca_engine import CA

def circle():
    xx, yy = np.mgrid[:20, :20]
    d = (xx - 10) ** 2 + (yy - 10) ** 2
    circ = np.where(d < 64, 1, 0)

def main():
    # Initialise empty np array
    mock_ca = np.zeros((20, 20), dtype=np.uint32)
    # Turn that into our basic CA
    life_ca = CA(mock_ca)
    life_ca[9, 10] = 1
    life_ca[10, 10] = 1
    life_ca[11, 10] = 1
    # Initialise a few cells
    ca_rep = CARep(life_ca.array)
    test_display = TextDisplay(ca_rep)
    test_display.display()
    life_ca.update()
    test_display.array = life_ca.array
    test_display.display()
    
if __name__ == '__main__':
    main()
