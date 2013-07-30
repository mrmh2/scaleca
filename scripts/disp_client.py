#!/usr/bin/env python
"""disp_client.py - simple text display client.

Connects to server, then constructs simple update loop which sends a command to
the server to run a simulation timestep, then displays the results."""

import os
import sys

import zmq
import numpy as np


def setup():
    parent, cdir = os.path.split(os.path.dirname(__file__))
    sys.path.append(parent)
    from scaleca.disp_simple import CADisplay
    globals()['CADisplay'] = CADisplay

def connect_to_server(port):
    context = zmq.Context()
    #print "Connecting to server..."
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:%s" % port)

    return socket

def string_state_to_array(sstate, shape):
    c_sep = ','.join(sstate)
    one_d = np.fromstring(c_sep, dtype=np.uint8, sep=',')
    return one_d.reshape(shape)

def unpack_string_rep(sstate):
    dim, astring = sstate.split(':')
    shape = map(int, dim.split(','))
    astate = string_state_to_array(astring, shape)

    return astate

def make_update_loop(socket):
    def update_loop():
        socket.send('RUN')
        message = socket.recv()
        return unpack_string_rep(message)

    return update_loop

def main():
    setup()
    port = "5556"
    socket = connect_to_server(port)

    ul = make_update_loop(socket)

    display = CADisplay()

    display.run_display(ul)

if __name__ == '__main__':
    main()
