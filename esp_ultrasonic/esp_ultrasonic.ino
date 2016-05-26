#include <Arduino.h>

#include <ESP8266WiFi.h>

const char* ssid     = "@ESPertAP_001";
const char* password = "espertap";


int trigPin = 5;    
int echoPin = 4;   
long duration, cm, inches;

void connectWifi();
void reconnectWifiIfLinkDown();
void uploadThingsSpeak(float t, float h, float moi);

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
}
