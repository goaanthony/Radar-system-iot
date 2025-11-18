#include <Arduino.h>

#define ULTRASON
#define WIFICLIENT
#define SERVOMOTEUR
#define MQTTCLIENT

#if defined(WIFICLIENT)
#include "wifi_custom.hpp"
#endif

#if defined(MQTTCLIENT)
#include "mqtt_custom.hpp"
#endif

#if defined(SERVOMOTEUR)
  #include <ESP32Servo.h>
  #define PIN_SG90 13
  Servo radarServo;

  int direction = 1;
  unsigned long lastServoMove = 0; // Timing pour le mouvement fluide
  const unsigned long SERVO_MOVE_INTERVAL = 15; // Mouvement toutes les 15ms
#endif

#if defined(ULTRASON)  
  #define TRIG_PIN 27
  #define ECHO_PIN 26

long duration = 0;
  int distance = -1; // -1 = hors de portée / non mesuré
#endif

/**
 * @brief Initialise les différents composant de l'ESP32
 * 
 * @details 
 * 
 */
void setup() {
  Serial.begin(115200);

#if defined(WIFICLIENT)
  setupWifi();
#endif

#if defined(SERVOMOTEUR)  
  radarServo.attach(PIN_SG90);
  Serial.println("Test SG90");
#endif

  #if defined(ULTRASON)  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Test HC-SR04");
#endif

#if defined(MQTTCLIENT)
    Serial.print("mqtt_server : ");
    Serial.println(mqtt_server);

    Serial.print("mqtt_port : ");
    Serial.println(mqtt_port);

    client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
#endif

}

#if defined(SERVOMOTEUR)  
  int angle = 0;
  int step = 1; 
#endif

void loop() {
  // CORRECTION : Déclaration de 'now' une seule fois, en dehors des #if
  unsigned long now = millis(); 

  // --- 6.1 GESTION DU SERVOMOTEUR (Tâche non-bloquante de 15ms) ---
  #if defined(SERVOMOTEUR)
    if (now - lastServoMove >= SERVO_MOVE_INTERVAL) { 
      lastServoMove = now; 

      radarServo.write(angle);
      angle += step * direction;

      if(angle >= 180) direction = -1;
      if(angle <= 0) direction = 1;   
    }
  #endif

  #if defined(ULTRASON)  
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 20000); 
    
    // Traitement de la distance
    if (duration > 0) { 
      distance = duration * 0.034 / 2; 

      if (distance > 400 || duration >= 100000) { 
        distance = 400;
      }
    } else {
        distance = 400; 
    }
  #endif

  #if defined(MQTTCLIENT)
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    // Publication des données toutes les 100ms
    if (now - lastMsg > 100) {
      lastMsg = now;

      // Construction du JSON
      snprintf(
        msg,
        MSG_BUFFER_SIZE,
        // Format JSON : {"angle": [int], "distance": [int]}
        R"({"angle":%d,"distance":%d})",
        
      #if defined(SERVOMOTEUR)
        angle,
      #else
        -1,
      #endif
      #if defined(ULTRASON)
        distance
      #else
        -1
      #endif
      );

      Serial.print("Publish message: ");
      Serial.println(msg);
      client.publish("RadarB2Ynov", msg);
    }
  #endif
}


// lucas notin elise tyselier clara
