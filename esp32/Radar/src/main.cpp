#include <Arduino.h>
#define ULTRASON
#define WIFICLIENT
#define SERVOMOTEUR

#if defined(WIFICLIENT)
  #include <WiFi.h>
  const char* ssid = "Bigo";
  const char* mdp = "pipicaca";
#endif


#if defined(MQTTCLIENT)
  #include <PubSubClient.h>
#endif


#if defined(SERVOMOTEUR)
  #include <ESP32Servo.h>
  #define PIN_SG90 13
  Servo radarServo;
#endif

#if defined(ULTRASON)  
  #define TRIG_PIN 27
  #define ECHO_PIN 26

  long duration;
  int distance;
#endif

#if defined(WIFICLIENT)
  /**
   * @brief Initialise et connecte l'ESP32 au réseau WiFi.
   *
   * @details
   * Démarre la connexion WiFi en utilisant les identifiants globaux `ssid` et `mdp`.
   * Affiche des informations sur le moniteur série :
   *  - affiche le nom du réseau visé,
   *  - confirme la connexion.
   */
  void setupWifi() {
    delay(100);
    Serial.print("\nConnexion a :");
    Serial.println(ssid);

    WiFi.begin(ssid, mdp);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(100);
      Serial.print("-");
    }
    
    Serial.print("\nConnecte a :");
    Serial.println(ssid);
  }
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
}

#if defined(SERVOMOTEUR)  
  int angle = 0;
  int step = 1; 
  int direction = 1;
#endif

void loop() {
  // --- Boucle servo de 0° à 180° et retour ---
  #if defined(SERVOMOTEUR)  
    radarServo.write(angle);
    delay(15); // ajuster vitesse

    angle += step * direction;

    if(angle >= 180) direction = -1;
    if(angle <= 0) direction = 1;   

    Serial.print("servo angle: ");
    Serial.println(angle);  
  #endif

  #if defined(ULTRASON)  
    // --- Lecture distance HC-SR04 ---
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2; 

    Serial.print("° - Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  #endif

  // controle vitesse servo
  // delay(1000); 
}



// lucas notin elise tyselier clara
