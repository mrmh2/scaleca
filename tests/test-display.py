#!/usr/bin/env python
import os
import sys

import numpy as np

parent, cdir = os.path.split(os.path.dirname(__file__))
sys.path.append(parent)
from scaleca.ca_display import CARep, TextDisplay, CursesDisplay
from scaleca.ca_life import CA

def test_curses_display(ca):
    curse_display = CursesDisplay(ca)
    curse_display.display_run(80, 0.001)

def main():

    life_ca = CA(36, 149)
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
