#!/usr/bin/env python

import numpy as np
from ca_display import CARep, TextDisplay, CursesDisplay
from ca_engine import CA


def test_curses_display(ca):
    curse_display = CursesDisplay(ca)
    curse_display.display_run(50, 0.1)

def main():
    # Initialise empty np array
    # Turn that into our basic CA
    life_ca = CA(35, 50)
    life_ca.fill_random()

#    life_ca.save_as_png('start.png')
#    life_ca.load_state('pentomino.ca')

    #life_ca.update_vote()
    test_curses_display(life_ca)

    # test_display = TextDisplay(ca_rep)
    # test_display.display()
    # life_ca.update()

    # test_display.display()
    
if __name__ == '__main__':
    main()
