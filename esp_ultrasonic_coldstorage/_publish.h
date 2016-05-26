#include <MqttConnector.h>

MqttConnector::prepare_data_hook_t on_prepare_data =
[&](JsonObject * root) -> void {
  float t_dht = 0;
  float h_dht = 0;
  int detect;
  R_ultrasonic();
  if(cm < 60)  {
    detect = 1;
  }
  else {
    detect = 0;
  }
  
  JsonObject& data = (*root)["d"];
  JsonObject& info = (*root)["info"];

  data["myName"] = DEVICE_NAME;
  data["millis"] = millis();
  data["temp"] = t_dht;
  data["humid"] = h_dht;
  data["Detect"] = detect;
};

void R_ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = (duration / 2) / 29.1;
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(250);
}

