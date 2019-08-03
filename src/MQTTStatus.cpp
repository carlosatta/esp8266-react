#include <MQTTStatus.h>

MQTTStatus::MQTTStatus(AsyncWebServer *server, SecurityManager* securityManager, MQTTClient* mqtt) : _server(server), _securityManager(securityManager), _mqtt(*mqtt) {
  _server->on(MQTT_STATUS_SERVICE_PATH, HTTP_GET, 
    _securityManager->wrapRequest(std::bind(&MQTTStatus::mqttStatus, this, std::placeholders::_1), AuthenticationPredicates::IS_AUTHENTICATED)
  );
}

void MQTTStatus::mqttStatus(AsyncWebServerRequest *request) {
  AsyncJsonResponse * response = new AsyncJsonResponse(MAX_MQTT_STATUS_SIZE);
  JsonObject root = response->getRoot();
  

  root["status"] = (int) _mqtt.connected();
  Serial.print("Status: ");
  Serial.println(_mqtt.connected());

  response->setLength();
  request->send(response);
}
