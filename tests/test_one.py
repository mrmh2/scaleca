import os
import sys

parent, cdir = os.path.split(os.path.dirname(__file__))
sys.path.append(parent)
from ca_display import CARep, TextDisplay, CursesDisplay
from scaleca.ca_life import CA

def test_one():
    life_ca = CA(10, 10)

    assert life_ca.array.shape == (10, 10)

def main():
    test_one()

if __name__ == '__main__':
    main()
