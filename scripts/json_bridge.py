#!/usr/bin/env python

import string
import random
import textwrap

import numpy as np
import zmq
from flask import Flask, render_template, make_response, request, g, session

app = Flask(__name__)

def connect_to_server(port):
    context = zmq.Context()
    #print "Connecting to server..."
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://localhost:%s" % port)

    return socket

def chunk(input, size):
    """Split iterator input into chunks of size size"""
    return map(None, *([iter(input)] * size))

def flurble_rep(message):
    dim, array = message.split(':')

    tr = string.maketrans('01', ' *')

    nrow, ncol = map(int, dim.split(','))
    
    split_array = textwrap.wrap(array, ncol)

    nl_array = '\n'.join([a.translate(tr) for a in split_array])

    return '<pre>' + nl_array + '</pre>'

#    return '<code>' + split_array[0] + '<br>' + split_array[1] + '</code>'


@app.route("/cainterface")
def run_and_return():

    port = "5556"
    socket = connect_to_server(port)

    socket.send('RUN')
    message = socket.recv()

    resp_string = flurble_rep(message)
    
    response = make_response(resp_string)
    # Setting header to allow cross site scripting
    # Sett http://stackoverflow.com/questions/9310112/why-am-i-seeing-an-origin-is-not-allowed-by-access-control-allow-origin-error
    response.headers.add('Access-Control-Allow-Origin', '*')
    
    return response

if __name__ == '__main__':
    app.run(debug=True)
