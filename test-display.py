#!/usr/bin/env python

import numpy as np
from cadisplay import CARep, TextDisplay

def main():
    mock_ca = np.zeros((20, 20), dtype=np.uint32)
    xx, yy = np.mgrid[:20, :20]
    d = (xx - 10) ** 2 + (yy - 10) ** 2
    circ = np.where(d < 64, 1, 0)
    ca_rep = CARep(circ)

    
    test_display = TextDisplay(ca_rep)
    test_display.display()

    
if __name__ == '__main__':
    main()
