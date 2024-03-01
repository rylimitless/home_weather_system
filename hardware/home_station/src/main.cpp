#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>

#define dhtPin 23
#define dhtType DHT22

//Contructors

Adafruit_BMP280 bmp; // I2C
DHT dht(dhtPin, dhtType);

bool checkDHT(float t, float h);

//TODO: add error checking for the DHT sensor

void setup() {
  Serial.begin(9600);
  dht.begin();
  while(!bmp.begin(0x76)){
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    delay(1000);
  }


}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float p = bmp.readPressure();
  float a = bmp.readAltitude(1013.25);
  float t2 = bmp.readTemperature();

  float temp = (t + t2) / 2;
  if (!checkDHT(t, h)){
    Serial.println("Error reading from DHT sensor");
    
  }else {
  Serial.printf("Temperature %.2f C \t Humidity %.2f\n", temp, h);
  Serial.printf("Pressure %.2f Pa \t Approximate Altitude %.2f\n", p, a);

  }
  delay(2000);
  // put your main code here, to run repeatedly:
}


//Function to check dht readings

bool checkDHT(float t, float h){
  if (isnan(t) || isnan(h)){
    return false;
  }
  return true;
}