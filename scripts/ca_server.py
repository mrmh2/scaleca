#!/usr/bin/env python
"""ca_server.py - start a server on a given port. The server will listen for
requests, and respond as follows:

'RUN' - run a single timestep of the CA and return the updated state"""

import os
import sys

import zmq

def setup():
    parent, cdir = os.path.split(os.path.dirname(__file__))
    sys.path.append(parent)
    from scaleca.ca_life import CA
    globals()['CA'] = CA

def init_server(port):
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind("tcp://*:%s" % port)

    return socket

def listen_loop(socket, ca):

    count = 0
    fmap = {'RUN': run_sim}

    while True:
        # Blocking wait        
        message = socket.recv()
        print "Received request:", message, count
        count += 1
        ret = 'UNKNOWN'
        if message in fmap:
            ret = fmap[message](ca)
        socket.send(ret)

def main():
    setup()
    port = "5556"
    socket = init_server(port)
    test_ca = CA(10, 10)
    test_ca[5,5] = 1
    test_ca[5,4] = 1
    test_ca[5,6] = 1

    listen_loop(socket, test_ca)

def run_sim(ca):
    ca.update()
    return ca.get_state_as_string()



if __name__ == '__main__':
    main()
