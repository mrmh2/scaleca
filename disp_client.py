#!/usr/bin/env python

import zmq
import numpy as np

from scaleca.disp_simple import CADisplay

port = "5556"

context = zmq.Context()
#print "Connecting to server..."
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:%s" % port)

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

ul = make_update_loop(socket)

display = CADisplay()

display.run_display(ul)
