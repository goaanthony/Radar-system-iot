#include "mqtt_custom.hpp"

#include <WiFiClient.h>
#include <PubSubClient.h>

// Configuration MQTT
const char* mqtt_server   = "broker.emqx.io";   // hôte sans schéma
const int   mqtt_port     = 1883;               // Port MQTT non sécurisé (plain TCP)

WiFiClient espClient; 
PubSubClient client(espClient);
unsigned long lastMsg = 0;
const int MSG_BUFFER_SIZE = 128;
char msg[MSG_BUFFER_SIZE];
int value = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Connexion sécurisée : on ne vérifie pas le certificat (à sécuriser pour la prod)
  // espClient.setInsecure(); // NON NÉCESSAIRE AVEC WiFiClient

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    Serial.print("clientId : ");
    Serial.println(clientId);

    // Connexion avec identifiant et éventuellement mot de passe
    if ( client.connect(clientId.c_str())) {
      Serial.println("connected to EMQX");
      client.subscribe("qefsgrdhftgj");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}