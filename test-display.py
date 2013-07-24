#!/usr/bin/env python

import numpy as np
from ca_display import CARep, TextDisplay, CursesDisplay
from ca_engine import CA


def test_curses_display(ca):
    curse_display = CursesDisplay(ca)
    curse_display.display_run(50, 0.05)

def main():
    # Initialise empty np array
    mock_ca = np.zeros((30, 30), dtype=np.uint32)
    # Turn that into our basic CA
    life_ca = CA(mock_ca)

    life_ca.load_state('states/glider.ca')

#    life_ca.load_state('pentomino.ca')

    test_curses_display(life_ca)

    # test_display = TextDisplay(ca_rep)
    # test_display.display()
    # life_ca.update()

    # test_display.display()
    
if __name__ == '__main__':
    main()
