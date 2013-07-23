"""CA display"""

import curses
import time

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

class CursesDisplay(object):

    def __init__(self, ca):
        self.ca = ca

    def display_run(self, n_frames):
        stdscr = curses.initscr()
        curses.cbreak()
        curses.noecho()
        value_map = {0: '  ', 1: '**'}
        for n in range(0, n_frames):
            #print self.ca.array
            for (r, row) in enumerate(self.ca.array):
                str_rep = ''.join(value_map[c] for c in row)
                stdscr.addstr(r, 0, str_rep)
                
            stdscr.refresh()
            self.ca.update()
            time.sleep(0.5)

        curses.nocbreak()
        curses.echo()
        curses.endwin()

        
        
