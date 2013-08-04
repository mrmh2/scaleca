"""Test the ca_server class"""

import os
import sys
import time
import multiprocessing

import zmq
import numpy as np

def setup():
    parent, cdir = os.path.split(os.path.dirname(__file__))
    sys.path.append(parent)
    from scaleca.ca_server import CAServer
    from scaleca.cas.ca_life import CA
    globals()['CA'] = CA
    globals()['CAServer'] = CAServer
    #from scaleca.disp_simple import CADisplay
    #globals()['CADisplay'] = CADisplay

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

def run_server():
    ca = CA(20, 20)
    #ca.fill_random()
    ca[10, 10] = 1
    caserver = CAServer(ca)
    caserver.serve_forever()

def main():
    setup()
    p = multiprocessing.Process(target=run_server)
    p.start()
    time.sleep(1)

    socket = connect_to_server('5556')
    socket.send('GETSTATE')
    message = socket.recv()
    state = unpack_string_rep(message)
    assert(state[10, 10] == 1)

    p.terminate()

if __name__ == '__main__':
    main()
