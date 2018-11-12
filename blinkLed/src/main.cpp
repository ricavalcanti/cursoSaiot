#include <Arduino.h>
#define pinLed LED_BUILTIN

void blinkLed(bool estado){
  digitalWrite(pinLed,!estado);
}
void setup() {
  pinMode(pinLed,OUTPUT);

}

void loop() {
  blinkLed(1);
  delay(500);
  blinkLed(0);
  delay(500);
}