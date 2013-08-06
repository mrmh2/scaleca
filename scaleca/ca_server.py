import zmq

def run_sim(ca, args):
    ca.update()
    return ca.get_state_as_string()

def get_state(ca, args):
    return ca.get_state_as_string()

def set_cell(ca, args):
    try:
        row, col, value = args
    except IndexError:
        print 'Error interpreting SETSTATE args'
        return 'ERROR'

    try:
        ca[row, col] = value
    except IndexError:
        print 'Error setting ca value'
        return 'ERROR'

    return 'SET'

def set_state(ca, args):
    pass

fmap = {'RUN' : run_sim,
        'GETSTATE': get_state,
        'SETSTATE': set_state,
        'SETCELL': set_cell}


class CAServer(object):
    """Class that exists to serve a CA"""

    def __init__(self, ca, port='5556'):
        self.ca = ca
        self.port = port

    def serve_forever(self):
        self.init_server()

        while True:
            message = self.socket.recv()

            margs = message.split()
            command = margs[0]
            try:
                args = margs[1:]
            except IndexError:
                args = NULL

            print 'Received:', command, args
            ret = fmap[command](self.ca, args)
            self.socket.send(ret)
        
    def init_server(self):
        context = zmq.Context()
        socket = context.socket(zmq.REP)
        socket.bind("tcp://*:%s" % self.port)
        print 'Initialised server on port', self.port

        self.socket = socket
