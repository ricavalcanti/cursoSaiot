#include <Arduino.h>
#include <SaIoTDeviceLib.h>
#define pinSensor A0
#define timeToPrint 3 //em segundos

//Objetos obrigatorios lib
WiFiClient espClient;
void callback(char *topic, byte *payload, unsigned int length);

//Device #####################################################################################
//Mudar parâmetros para o seu email cadastrado e sua senha
SaIoTDeviceLib deviceBrightness("deviceBrightness", "SERIALUNIC", "seuEmail@email.com");
String senha = "suaSenha";

//Sensor ################################################################################
SaIoTSensor sensorLDR("ldr01","sensorLDR", "%", "number");

//Variaveis sensor
long val, sensorMax = 1024, sensorMin = 0;
unsigned long int lastTime;

void setup()
{
  deviceBrightness.addSensor(sensorLDR);
  Serial.begin(115200);
  Serial.println("INICIO");
  pinMode(pinSensor, INPUT);
  deviceBrightness.preSetCom(espClient, callback);
  deviceBrightness.startDefault(senha);
  lastTime = millis();
}

void loop()
{
      if ((((millis() - lastTime) / 1000) >= timeToPrint))
    {
        val = analogRead(pinSensor);
        Serial.print("Valor sensor: ");
        val = map(val, 0, sensorMax, 0, 100);
        sensorLDR.sendData(val); //saveData
        lastTime = millis();
    }
    deviceBrightness.handleLoop();
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
    if (strcmp(topic, deviceBrightness.getSerial().c_str()) == 0)
    {
        Serial.println("SerialLog: " + payloadS);
    }
}