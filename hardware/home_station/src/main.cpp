#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

#define dhtPin 23
#define dhtType DHT22
#define soilpin 34

// Contructors


const char *ssid = "MonaConnect";
const char *password = "";

//MQTT client
const char *broker = "www.yanacreations.com";
const int port = 1883;

Adafruit_BMP280 bmp; // I2C
DHT dht(dhtPin, dhtType);

WiFiClient espClient;
PubSubClient client(espClient);

bool checkDHT(float t, float h);
String toDocument(float t, float h, float p, float a, int soil);
// TODO: add error checking for the DHT sensor

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(!WiFi.isConnected()){
    Serial.printf("Connecting to wifi network %s\n",ssid);
    delay(1000);
  }
  if(WiFi.isConnected()){
    Serial.println("Connected to wifi nework");
  }
  client.setServer("www.yanacreations.com",port);
  
  while(!client.connect("test1")){
    Serial.println("connecting");
    delay(1000);
  }

 
  dht.begin();
  while (!bmp.begin(0x76))
  {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    delay(1000);
  }
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p = bmp.readPressure();
  float a = bmp.readAltitude(1013.25);
  float t2 = bmp.readTemperature();
  int soil = analogRead(soilpin);

  float temp = (t + t2) / 2;
  if (!checkDHT(t, h))
  {
    Serial.println("Error reading from DHT sensor");
  }
  else
  {
    // Serial.printf("Temperature %.2f C \t Humidity %.2f\n", temp, h);
    // Serial.printf("Pressure %.2f Pa \t Approximate Altitude %.2f\n", p, a);
    // Serial.printf("Soil Moisture: %d\n", soil);
    const char  *doc = toDocument(temp, h, p, a, soil).c_str();

    client.publish("topic1",doc);
    Serial.println("Published");
  }

  delay(2000);
  // put your main code here, to run repeatedly:
}

// // Function to check dht readings

bool checkDHT(float t, float h)
{
  if (isnan(t) || isnan(h))
  {
    return false;
  }
  return true;
}


String toDocument(float t, float h, float p, float a, int soil) {
  JsonDocument doc;
  doc["temperature"] = t;
  doc["humidity"] = h;
  doc["pressure"] = p;
  doc["altitude"] = a;
  doc["soil"] = soil;
  String output;
  serializeJson(doc, output);
  return output;
}