#include <Arduino.h>
#include <SaIoTDeviceLib.h>
#define pinLed LED_BUILTIN

//Funções para fazer o led piscar
void blinkLed(bool estado)
{
  digitalWrite(pinLed, !estado);
}

//Objetos obrigatorios lib
WiFiClient espClient;
void callback(char *topic, byte *payload, unsigned int length);

//Device #####################################################################################
//Mudar parâmetros para o seu email cadastrado e sua senha
SaIoTDeviceLib interruptor("Device_interruptor", "SERIALUNICO", "seuEmail@email.com");
String senha = "suaSenha";

//Controlador ################################################################################
SaIoTController contOnOff("intpS", "interruptorLab", "onoff");

void setup()
{
  pinMode(pinLed, OUTPUT);
  interruptor.addController(contOnOff);
  Serial.begin(115200);
  Serial.println("START");
  digitalWrite(pinLed, LOW);
  interruptor.preSetCom(espClient, callback);
  interruptor.startDefault(senha);
  digitalWrite(pinLed, HIGH);
}

void loop()
{
  interruptor.handleLoop();
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String payloadS;
    Serial.print("Topic: ");
    Serial.println(topic);
    for (unsigned int i = 0; i < length; i++)
    {
        payloadS += (char)payload[i];
    }
    if (strcmp(topic, interruptor.getSerial().c_str()) == 0)
    {
        Serial.println("SerialLog: " + payloadS);
    }
    if (strcmp(topic, (interruptor.getSerial() + contOnOff.getKey()).c_str()) == 0)
    {
        Serial.println("SerialLog: " + payloadS);
        blinkLed(bool(payloadS.toInt()));
    }
}