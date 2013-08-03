import zmq

def run_sim(ca):
    ca.update()
    return ca.get_state_as_string()

def get_state():
    pass

def set_state():
    pass

fmap = {'RUN' : run_sim,
        'GETSTATE': get_state,
        'SETSTATE': set_state}


class CAServer(object):
    """Class that exists to serve a CA"""

    def __init__(self, ca, port='5556'):
        self.ca = ca
        self.port = port

    def serve_forever(self):
        self.init_server()

        while True:
            message = self.socket.recv()
            print 'Received:', message
            ret = fmap[message](self.ca)
            self.socket.send(ret)
        
    def init_server(self):
        context = zmq.Context()
        socket = context.socket(zmq.REP)
        socket.bind("tcp://*:%s" % self.port)
        print 'Initialised server on port', self.port

        self.socket = socket
