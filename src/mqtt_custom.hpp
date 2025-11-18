#ifndef mqtt_CUSTOM
#define mqtt_CUSTOM

#include <WiFi.h>
#include <PubSubClient.h>

extern const char* mqtt_server;
extern const int   mqtt_port;

extern WiFiClient espClient;
extern PubSubClient client;
extern unsigned long lastMsg;
extern const int MSG_BUFFER_SIZE;
extern char msg[];
extern int value;

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

#endif