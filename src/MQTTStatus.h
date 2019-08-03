#ifndef MQTTStatus_h
#define MQTTStatus_h

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP_PLATFORM)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncArduinoJson6.h>
#include <SecurityManager.h>

#include <MQTT.h>

#define MAX_MQTT_STATUS_SIZE 1024
#define MQTT_STATUS_SERVICE_PATH "/rest/mqttStatus"

class MQTTStatus {

  public:

    MQTTStatus(AsyncWebServer *server, SecurityManager* securityManager, MQTTClient* mqtt);

  private:

    AsyncWebServer* _server;
    SecurityManager* _securityManager;

    MQTTClient _mqtt;

    void mqttStatus(AsyncWebServerRequest *request);

};

#endif // end MQTTStatus_h
