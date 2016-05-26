#include <Arduino.h>
#include <Arduino.h>
#include <MqttConnector.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

void init_hardware();


void setup();

void loop();
#line 9 "esp_ultrasonic_mqtt.ino"
DHT dht(DHTPIN, DHTTYPE);

MqttConnector *mqtt;

#define MQTT_HOST         "mqtt.espert.io"
#define MQTT_PORT         1883
#define MQTT_USERNAME     ""
#define MQTT_PASSWORD     ""
#define MQTT_CLIENT_ID    ""
#define MQTT_PREFIX       "/CMMC"
#define PUBLISH_EVERY     (3*1000)// every 10 seconds


#define DEVICE_NAME       "CNX-CMMC-Ultrasonics"

#ifndef WIFI_SSID
#define WIFI_SSID        "@ESPertAP_001"
#define WIFI_PASSWORD    "espertap"
#endif

int trigPin = 5;
int echoPin = 4;
long duration, cm, inches;

#include "_publish.h"
#include "_receive.h"
#include "init_mqtt.h"

void init_hardware()
{
Serial.begin(115200);
delay(10);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
Serial.println();
Serial.println("Serial port initialized.");
}


void setup()
{
init_hardware();

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while(WiFi.status() != WL_CONNECTED) {
Serial.printf ("Connecting to %s:%s\r\n", WIFI_SSID, WIFI_PASSWORD);
delay(300);
}
Serial.println("WiFi Connected.");

init_mqtt();
}

void loop()
{
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);

cm = (duration/2) / 29.1;

Serial.print(inches);
Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();

delay(250);
mqtt->loop();
}