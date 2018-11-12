#include <Arduino.h>
#define pinButton D4
#define pinLed LED_BUILTIN

void blinkLed(bool estado){
  digitalWrite(pinLed,!estado);
}

void setup() {
  pinMode(pinButton,INPUT_PULLUP);
}

void loop() {
  //Se o botal tiver apertado a leitura vai dar 0, se tiver solto vai dar 1
  blinkLed(!digitalRead(pinButton));
}