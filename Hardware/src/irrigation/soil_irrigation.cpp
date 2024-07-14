#include "Arduino.h"
#include "../hardware.h"
#include "soil_irrigation.h"
#include "Wire.h"

void IRRIGATION::setup() 
{
  //setup for the temperature and humidity sensors
  Wire.begin();
  sht.begin(0x44); //Sensor I2C Address
  Wire.setClock(100000);
  uint16_t stat = sht.readStatus();

  //ultrasonic sensor setup
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(MOS,OUTPUT);
}

//check temperature and humidity of plant
void IRRIGATION::tempHumidity()
{
  sht.read();
  Serial.print("Temperature:");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.print("Humidity:");
  Serial.println(sht.getHumidity(), 1);
}

//check water level using ultrasonic sensor
void IRRIGATION::tankWaterLevel() 
{
  int timeTaken;
  float distance;

  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);  
  timeTaken = pulseIn(ECHO, HIGH);

  if (timeTaken>0){
    distance = timeTaken/58.2;

    if(distance <= 4){            //can change distance according to height of our tank
      Serial.println("water level high");
    }
    else if(distance >= 7){
      Serial.println("water level low, fill water");
    }
  }
}

void IRRIGATION::readSoilMoisture()
{
  for(int i = 0; i<=100;i++){
    sensorValue = sensorValue + analogRead(SM);
    delay(1);
  }
  sensorValue = sensorValue/100;
}

//check soil moisture
void IRRIGATION::soilMoisture()
{
  readSoilMoisture();
  Serial.print("Moisture Sensor reading: ");
  Serial.print(sensorValue);
  Serial.print("\t");
  
  if(sensorValue < 300){
    Serial.println("Soil is Dry");
    waterPlant();
  }
  else if((sensorValue >= 300) && (sensorValue <= 700)){
    Serial.println("Soil is Humid");
    digitalWrite(MOS, LOW);
  }
  else if(sensorValue > 700){
    Serial.println("Soil is Wet");
    digitalWrite(MOS, LOW);
  }
}

void IRRIGATION::waterPlant()
{
  for(int i=0; i<1000; i++){   // waits for around 16 minutes if soil is still dry
    digitalWrite(MOS, HIGH);
    
    readSoilMoisture();
    
    if(sensorValue >=300){
      digitalWrite(MOS, LOW);
      delay(5000);
      Serial.println("Plant watering is complete");
      break;
    }
    
    delay(1000);
  }
}
