#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <math.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>


WiFiClient espClient;
PubSubClient client(espClient);


#define dhtPin 25
#define dhtType DHT22
#define soilpin 34

#define MAX 4095
#define MIN 0

#define TFT_DC 17
#define TFT_CS 5
#define TFT_RST 16
#define TFT_CLK 18
#define TFT_MOSI 23
#define TFT_MISO 19


const char *ntp_server ="pool.ntp.org";
const long  gmtOffset_sec = -5;
const int   daylightOffset_sec = 3600;

const char *ssid = "MonaConnect";
const char *password = "";

//MQTT client
const char *broker = "dbs.msjrealtms.com";
const int port = 1883;

Adafruit_BMP280 bmp; // I2C
DHT dht(dhtPin, dhtType);


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

bool checkDHT(float t, float h);
String toJson(float  , float , float , float , float);
float to2dp(float);
void init_connections();
float get_time_stamp();
void print_to_tft();
void draw_dashboard(float temperature, float soil, float humidity, float heatIndex, float pressure, float altitude);
// String toDocument(float t, float h, float p, float a, int soil);
// TODO: add error checking for the DHT sensor

void setup()
{
  Serial.begin(9600);


  dht.begin();
  while (!bmp.begin(0x76))
  {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    delay(1000);
  }

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);
  // tft.setTextColor(ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setTextSize(4);
  tft.setCursor(30,30);
  tft.println("WELCOME");
  delay(100);
  delay(1000);
  tft.fillScreen(ILI9341_BLACK);
  init_connections();
  configTime(gmtOffset_sec, daylightOffset_sec, ntp_server);
  get_time_stamp();
  tft.fillScreen(ILI9341_BLACK);
  // tft.drawRect(0, 0, tft.width(), tft.height(), ILI9341_WHITE);
}


void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p = bmp.readPressure();
  float a = bmp.readAltitude(1014.8);
  float t2 = bmp.readTemperature();
  int soil = analogRead(soilpin);
  Serial.println(soil);
  float soil_p = map(soil , 4095, 0 , 0 , 100);

  print_to_tft();

  draw_dashboard(t2, soil_p, h, dht.computeHeatIndex((t,h,false)), p, a);
  

  const char  *doc = toJson(t2,h,p,soil_p,a).c_str();

  bool published = client.publish("topic1",doc);
  if(published)
  Serial.println("Published");

  float temp = (t + t2) / 2;
  if (!checkDHT(t, h))
  {
    Serial.println("Error reading from DHT sensor");
  }
  else
  {
    Serial.printf("Temperature %.2f C \t Humidity %.2f\n", temp, h);
    Serial.printf("Pressure %.2f hPa \t Approximate Altitude %.2f m\n", p, a);
    Serial.printf("Soil Moisture: %.2f% \t Heat Index %.2f C\n\n\n", soil_p, dht.computeHeatIndex(t, h,false));
  }

    vTaskDelay(2000 / portTICK_PERIOD_MS); // Use vTaskDelay instead of delay
  
  // put your main code here, to run repeatedly:
}

bool checkDHT(float t, float h)
{
  if (isnan(t) || isnan(h))
  {
    return false;
  }
  return true;
}

void print_to_tft() {
  // Draw border
  tft.drawRect(0, 0, tft.width(), tft.height(), ILI9341_RED);
  tft.drawRect(1, 1, tft.width() - 2, tft.height() - 2, ILI9341_YELLOW);
  tft.drawRect(2, 2, tft.width() - 4, tft.height() - 4, ILI9341_GREEN);
  tft.drawRect(3, 3, tft.width() - 6, tft.height() - 6, ILI9341_BLUE);
}

void draw_dashboard(float temperature, float soil, float humidity, float heatIndex, float pressure, float altitude) {

  tft.setTextSize(2);

  // Set the text color and size
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);

  tft.setCursor(10, 10);
  tft.print("Temp: ");
  tft.print(temperature);
  tft.println(" C");
  tft.println("");

  tft.setTextColor(ILI9341_BLUE,ILI9341_BLACK);
  tft.setCursor(10, 40);
  tft.print("Soil: ");
  tft.print(soil);
  tft.println(" %");
  tft.println("");

  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setCursor(10, 70);
  tft.print("Humidity: ");
  tft.println(humidity);
  tft.println("");
  // tft.drawRect(8, 68, 100, 30, ILI9341_BLUE);

  tft.setTextColor(ILI9341_BLUE,ILI9341_BLACK);
  tft.setCursor(10, 100);
  tft.print("Heat Index: ");
  tft.println(heatIndex);


  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setCursor(10, 130); 
  tft.print("Pressure: ");
  tft.println(pressure);

  tft.setTextColor(ILI9341_BLUE,ILI9341_BLACK);
  tft.setCursor(10, 160);
  tft.print("Altitude: ");
  tft.println(altitude);

}

void init_connections(){
  Serial.println("Startinf");
  WiFi.begin(ssid,password);
  int retryCount = 0;
  int print = 0;
  while(!WiFi.isConnected() && retryCount < 10){
    if(print==0){
      tft.setTextSize(2);
      print=1;
      tft.printf("Connecting to wifi network %s", ssid);
    }
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
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    retryCount++;
  }
}

  String toJson(float avg_temperature , float humidity, float pressure, float soil_moisture , float aprox_altitude){
    JsonDocument doc;
    doc["temperature"] = ceil(avg_temperature * 100.0) / 100.0;
    doc["humidity"] = ceil(humidity * 100.0) /100.0;
    doc["pressure"] = ceil(pressure * 100.0) /100.0 ;
    doc["soil moisture"] = soil_moisture;
    doc["heat index"] = ceil(dht.computeHeatIndex(avg_temperature, humidity,false) * 100.0) / 100.0;
    doc["altitude"] = ceil(aprox_altitude * 100.0) / 100.0;
    String output;
    serializeJson(doc, output);
    return output;
  }