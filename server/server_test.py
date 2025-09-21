import threading
import time
from flask import Flask, request

app = Flask(__name__)
requests_list = []

# Initial routeCoordinates JSON data structure
routeCoordinates = {
    "13:00:00": [6.615066, -58.207886],
    "13:02:00": [6.616738, -58.207918],
    "13:05:00": [6.624742, -58.206212],
    "13:08:00": [6.627614, -58.202686],
    "13:10:00": [6.631833, -58.200004]
}

def log_requests():
    while True:
        # Log the contents of routeCoordinates to the console
        print("Route Coordinates:", routeCoordinates)
        # Wait for five seconds before logging again
        time.sleep(5)

# Start the background thread for logging routeCoordinates
logging_thread = threading.Thread(target=log_requests)
logging_thread.daemon = True
logging_thread.start()

@app.route('/', methods=['GET', 'POST'])
def handle_requests():
    if request.method == 'POST':
        # Log the contents of the POST request
        request_data = request.form.to_dict()
        log_message = f"Received POST request with data: {request_data}"
        print(log_message)  # This will print to the console

        print(request_data)

        # Extract latitude, longitude, and timestamp from the request data
        latitude = float(request_data.get('latitude'))
        longitude = float(request_data.get('longitude'))
        timestamp = request_data.get('timestamp')

        # Store the request data in the route coordinates dictionary
        routeCoordinates[timestamp] = [latitude, longitude]

        # Return an empty response for POST requests
        return '', 204
    elif request.method == 'GET':
        # Read the HTML file and return its contents as the response
        with open('index.html', 'r') as file:
            html_content = file.read()
        return html_content

from flask import jsonify

@app.route('/route_coordinates')
def get_route_coordinates():
    return jsonify(routeCoordinates)


if __name__ == '__main__':
    app.run(port=5000)
