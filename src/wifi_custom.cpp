#include "wifi_custom.hpp"

    const char* ssid = "iPhone de Anthony";
    const char* mdp = "1234567891011";

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
  Serial.print("\nConnexion a : ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, mdp);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("-");
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.print("\nConnecte a : ");
    Serial.println(ssid);

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

  } else {
    Serial.println("\nEchec connexion WiFi");
  }
}