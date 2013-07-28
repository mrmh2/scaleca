#!/usr/bin/env python

import zmq
from scaleca.ca_life import CA

def init_server(port):
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind("tcp://*:%s" % port)

    return socket

def main():
    port = "5556"
    socket = init_server(port)
    test_ca = CA(10, 10)
    test_ca[5,5] = 1
    test_ca[5,4] = 1
    test_ca[5,6] = 1

def run_sim(ca):
    ca.update()
    return ca.get_state_as_string()

fmap = {'RUN': run_sim}

count = 0
while True:
    # Blocking wait                                                                                                                                   
    message = socket.recv()
    print "Received request:", message, count
    count += 1
    ret = 'UNKNOWN'
    if message in fmap:
        ret = fmap[message](test_ca)

#    time.sleep(1)                                                                                                                                    
    socket.send(ret)
