"""disp_simple.py - simple CA display for testing.

Simply prints out array"""

import time

class CADisplay(object):

    def __init__(self):
        pass

    def run_display(self, callback, delay=None):
        """Main loop. callback should update and return array."""

        while True:
            array = callback()
            print array
