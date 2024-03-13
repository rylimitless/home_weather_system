#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <math.h>
#include <SPI.h>
#include <Adafruit_GFX.h>       // include Adafruit graphics library

#define dhtPin 25
#define dhtType DHT22
#define soilpin 34

// Contructors

#define TFT_DC 17
#define TFT_CS 5
#define TFT_RST 16
#define TFT_CLK 18
#define TFT_MOSI 23
#define TFT_MISO 19

const char *ssid = "MonaConnect";
const char *password = "";

//MQTT client
const char *broker = "www.yanacreations.com";
const int port = 1883;

Adafruit_BMP280 bmp; // I2C
DHT dht(dhtPin, dhtType);

WiFiClient espClient;
PubSubClient client(espClient);

bool checkDHT(float , float );
float get_heat_index(float, float);
String toDocument(float , float , float , float , int , float);
void init_connections();
// TODO: add error checking for the DHT sensor
struct Sensors {

  float temperature_a = 0.0;
  float temperature_b = 0.0;
  float humidity = 0.0;
  float pressure = 0.0;
  float aprox_altitude = 0.0;
  int soil_moisture = 0;
  float avg_temperature = 0.0;

  String toJson(){
    JsonDocument doc;
    doc["temperature"] = to2dp(this->avg_temperature);
    doc["humidity"] = to2dp(this->humidity);
    doc["pressure"] = to2dp(this->pressure);
    doc["soil moisture"] = this->soil_moisture;
    doc["heat index"] = this->get_heat_index();
    doc["altitude"] = to2dp(this->aprox_altitude);
    String output;
    serializeJson(doc, output);
    return output;
  }

  float get_heat_index(){
    float t = this->avg_temperature , r = this->humidity;
  float c1 , c2, c3, c4, c5, c6, c7, c8 , c9 , r2, t2;
  r2 = r*r , t2 = t*t;
  c1 = -42.379 , c2 = -2.04901523 , c3 =  -10.14333127 , c4 = -0.22475541;
  c5 = -6.83783 * pow(10,-3)  , c6 = -5.481717 * pow(10,-2);
  c7 = -1.22874 * pow(10,-3) , c8 = 8.5282 * pow(10,-4) , c9 = -1.99 * pow(10,-6);
  float heat_index = c1 + c2*t + c3 * r + c4 * t * r + c5 * t2;   
  heat_index += c6 * r2 + c7 * t2 * r + c8 * t * r2 + c9 * r2 * t2;
  return ceil(heat_index * 100.0)/ 100.0;
  }

  float to2dp(float quantity){
    return ceil(quantity * 100.0) /100.0;
  }

  void avg(){
    this->avg_temperature = (temperature_a + temperature_b) /2.0;
  }
};

Sensors sensor;

void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);
  init_connections();

  dht.begin();
  while (!bmp.begin(0x76))
  {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    delay(1000);
  }

}

void loop()
{
  sensor.humidity = dht.readHumidity();
  sensor.temperature_a = dht.readTemperature();
  sensor.pressure = bmp.readPressure();
  sensor.aprox_altitude = bmp.readAltitude(1013.25);
  sensor.temperature_b = bmp.readTemperature();
  sensor.soil_moisture = analogRead(soilpin);
  sensor.avg();
 
  const char  *doc = sensor.toJson().c_str();

  client.publish("topic1",doc);
  Serial.println("Published");

  Serial.printf("Temperature: %f\n",sensor.avg_temperature);
  delay(2000);
  // put your main code here, to run repeatedly:
}



void init_connections(){
  Serial.println("Startinf");
  WiFi.begin(ssid,password);
  int retryCount = 0;
  while(!WiFi.isConnected() && retryCount < 10){
    Serial.printf("Connecting to wifi network %s\n",ssid);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Use vTaskDelay instead of delay
    retryCount++;
  }
  if(WiFi.isConnected()){
    Serial.println("Connected to wifi nework");
  }
  client.setServer(broker,port);
  
  retryCount = 0;
  while(!client.connect("test1") && retryCount < 10){
    Serial.println("connecting");
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Use vTaskDelay instead of delay
    retryCount++;
  }
}

