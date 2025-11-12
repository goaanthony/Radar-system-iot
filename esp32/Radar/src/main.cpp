#include <Arduino.h>
#include <Servo.h>

#define PIN_SG90 19
#define LED 2

Servo sg90;

void setup() {
  pinMode(LED, OUTPUT);
  sg90.attach(PIN_SG90);
}

void loop() {
  // static unsigned long start = 0;
  // if (start == 0) start = millis();

  // if (millis() - start < 10000) {
  //   digitalWrite(LED, LOW);
  //   delay(500);
  //   digitalWrite(LED, HIGH);
  //   delay(500);
  // } else {
  //   digitalWrite(LED, LOW);
  //   for (;; ) delay(1000); 
  // }

  for (int pos = 0; pos <= 180; pos += 1) {
    sg90.write(pos);
    delay(10);
  }
  // Rotation de 180° à 0°
  for (int pos = 180; pos >= 0; pos -= 1) {
    sg90.write(pos);
    delay(10);
  }
}


// lucas notin elise tyselier clara
