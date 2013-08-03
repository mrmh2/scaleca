#!/usr/bin/env python
import os
import sys
import argparse
import importlib

def setup():
    parent, cdir = os.path.split(os.path.dirname(__file__))
    sys.path.append(parent)
    from scaleca.ca_server import CAServer
    globals()['CAServer'] = CAServer

def main():
    setup()

    parser = argparse.ArgumentParser()
    parser.add_argument('--port', '-p', help='port on which to start server (default 5556)', 
                        default='5556')
    parser.add_argument('--name', '-n', help='name of CA to serve (default ca_vote)',
                        default='ca_vote')
    parser.add_argument('--dim', '-d', help='dimension of CA, as RxC where R is rows and C is columns',
                        default='30x30')
    args = parser.parse_args()

    port = args.port
    ca_name = args.name
    raw_dim = args.dim

    dim = map(int, raw_dim.split('x'))

    ca_modname = 'scaleca.cas.' + ca_name
    CA = importlib.import_module(ca_modname)
    ca = CA.CA(*dim)
    ca.fill_random()
    ca_server = CAServer(ca, port=port)
    ca_server.serve_forever()

if __name__ == '__main__':
    main()
