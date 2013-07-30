import random

from flask import Flask, render_template, make_response, request, g, session

app = Flask(__name__)

@app.route("/cainterface")
def run_and_return():

    resp_string = 'Hello ' + str(random.randint(0, 10))
    
    response = make_response(resp_string)
    # Setting header to allow cross site scripting
    # Sett http://stackoverflow.com/questions/9310112/why-am-i-seeing-an-origin-is-not-allowed-by-access-control-allow-origin-error
    response.headers.add('Access-Control-Allow-Origin', '*')
    
    return response

if __name__ == '__main__':
    app.run(debug=True)
