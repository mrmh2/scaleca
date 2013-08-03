#!/usr/bin/env python
import os
import sys

def setup():
    parent, cdir = os.path.split(os.path.dirname(__file__))
    sys.path.append(parent)
    from scaleca.ca_server import CAServer
    globals()['CAServer'] = CAServer

def main():
    setup()

    from scaleca.cas.ca_life import CA
    ca = CA(30, 30)
    ca.fill_random()
    ca_server = CAServer(ca)
    ca_server.serve_forever()

if __name__ == '__main__':
    main()
