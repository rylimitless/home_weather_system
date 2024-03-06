#include <Sensors.h>

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