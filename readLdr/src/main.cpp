#include <Arduino.h>
#define pinSensor A0
#define timeToPrint 3 //em segundos

//Variaveis sensor
long val, sensorMax = 1024, sensorMin = 0;
unsigned long int lastTime;

void setup()
{
  Serial.begin(115200);
  pinMode(pinSensor, INPUT);
  lastTime = millis();
}

void loop()
{
  if ((((millis() - lastTime) / 1000) >= timeToPrint))
  {
    val = analogRead(pinSensor);
    Serial.print("Valor sensor: ");
    val = map(val, 0, sensorMax, 0, 100);
    //Serial.println(constrain(val,0,100));
    Serial.println(val);
    lastTime = millis();
  }
}