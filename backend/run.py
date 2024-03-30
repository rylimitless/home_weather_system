from flask import Flask, jsonify
from app.mqtt_client import mqttc
import app.constants as constants
import app.functions as functions


app = Flask(__name__)

@app.route("/app/hello")
def get():
    return jsonify({"success":"Hello World"})

@app.route("/app/data/<start>/<end>")
def get_data(start,end):
    start_time = float(start)
    end_time = float(end)
    result = functions.get_data(start_time,end_time)
    return {"data":result}

@app.route("/app/avg/<start>/<end>")
def get_avg(start,end):
    start_time = float(start)
    end_time = float(end)
    result = functions.get_avg(start_time,end_time)
    return {"avg":result}
    


def start_flask_app():
    app.run(port=5000,host='0.0.0.0')

def start_mqtt_client():
    mqttc.connect('broker.emqx.io',1883)
    mqttc.user_data_set([])
    mqttc.subscribe(constants.SUB_TOPIC)
    mqttc.loop_start()

if __name__ == "__main__":

    start_mqtt_client()
    start_flask_app()