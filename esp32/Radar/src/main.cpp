#include <Arduino.h>
#include <ESP32Servo.h>

#define PIN_SG90 13
#define TRIG_PIN 27
#define ECHO_PIN 26

Servo sg90;

long duration;
int distance;

void setup() {
  Serial.begin(115200);
  sg90.attach(PIN_SG90, 500, 2400);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Test SG90 + HC-SR04");
}

int angle = 0;
int step = 1; // sens du servo

void loop() {
  // --- Boucle servo de 0° à 180° et retour ---
  angle += step;
  if (angle >= 180 || angle <= 0) step = -step; // inverse le sens
  sg90.write(angle);

  // --- Lecture distance HC-SR04 ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // distance en cm

  Serial.print("Angle servo: ");
  Serial.print(angle);
  Serial.print("° - Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(20); // contrôle vitesse servo
}



// lucas notin elise tyselier clara
