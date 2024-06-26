from flask import Flask, jsonify
from app.mqtt_client import mqttc
import app.constants as constants

app = Flask(__name__)

@app.route("/")
def get():
    return {"success":"Hello World"}

# @app.route("/")

def start_flask_app():
    app.run(port=5000)

def start_mqtt_client():
    mqttc.connect('dbs.msjrealtms.com',1883)
    mqttc.user_data_set([])
    mqttc.subscribe(constants.SUB_TOPIC)
    mqttc.loop_start()

if __name__ == "__main__":

    start_mqtt_client()
    start_flask_app()