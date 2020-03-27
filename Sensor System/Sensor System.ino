#include <Wire.h>
#include <BH1750.h>

#include <Adafruit_Sensor.h>
#include "DHT.h"

#define DHTPIN 13    
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter(0x23);

float lux;


const int voltageSensor1 = A1;
float vOUT1 = 0.0;
float vIN1 = 0.0;
float R11 = 30000.0;
float R21 = 7500.0;
int value1 = 0;

const int voltageSensor2 = A3;
float vOUT2 = 0.0;
float vIN2 = 0.0;
float R12 = 30000.0;
float R22 = 7500.0;
int value2 = 0;



const int currentPin1 = A0;
int sensitivity1 = 185;
int adcValue1= 0;
int offsetVoltage1 = 2500;
double adcVoltage1 = 0;
double currentValue1 = 0;



const int currentPin2 = A2;
int sensitivity2 = 185;
int adcValue2= 0;
int offsetVoltage2 = 2500;
double adcVoltage2 = 0;
double currentValue2 = 0;

void setup() {
  Serial.begin(115200);
   lightMeter.begin();
  Wire.begin();

  dht.begin();
}

void loop() {

 delay(500);
  value1 = analogRead(voltageSensor1);
  vOUT1 = (value1 * 5.0) / 1024.0;
  vIN1 = vOUT1 / (R21/(R11+R21));

  value2 = analogRead(voltageSensor2);
  vOUT2 = (value2 * 5.0) / 1024.0;
  vIN2 = vOUT2 / (R22/(R12+R22));

  adcValue1 = analogRead(currentPin1);
  adcVoltage1 = (adcValue1 / 1024.0) * 5000;
  currentValue1 = -1*((adcVoltage1 - offsetVoltage1) / sensitivity1);

  adcValue2 = analogRead(currentPin2);
  adcVoltage2 = (adcValue2 / 1024.0) * 5000;
  currentValue2 = -1*((adcVoltage2 - offsetVoltage2) / sensitivity2);
  

  
 lux = ((lightMeter.readLightLevel())*34.25)/160;
 // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
   
 // Check if any reads failed and exit early (to try again).
  if (isnan(lux) || isnan(h) || isnan(t)) {
    Serial.println("0 , 0 , 0 , 0 , 0");
    return;
 
  }
  Serial.print(lux);
  Serial.print(" , ");
  Serial.print(h);
  Serial.print(" , ");
  Serial.print(t);
  Serial.print(" , ");
  Serial.print(vIN1);
  Serial.print(" , ");
  Serial.print(currentValue1);
  Serial.print(" , ");
  Serial.print(vIN2);
  Serial.print(" , ");
  Serial.println(currentValue2);
  
  delay(30000);
   
 
}
