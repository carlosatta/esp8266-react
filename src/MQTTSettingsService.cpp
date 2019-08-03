#include <MQTTSettingsService.h>

// MQTTClient mqtt;
WiFiClient client;

MQTTSettingsService::MQTTSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager, MQTTClient* mqtt) : AdminSettingsService(server, fs, securityManager, MQTT_SETTINGS_SERVICE_PATH, MQTT_SETTINGS_FILE), _mqtt(*mqtt) {

#if defined(ESP8266)
  _onStationModeDisconnectedHandler = WiFi.onStationModeDisconnected(std::bind(&MQTTSettingsService::onStationModeDisconnected, this, std::placeholders::_1));
  _onStationModeGotIPHandler = WiFi.onStationModeGotIP(std::bind(&MQTTSettingsService::onStationModeGotIP, this, std::placeholders::_1));
#elif defined(ESP_PLATFORM)
  WiFi.onEvent(std::bind(&MQTTSettingsService::onStationModeDisconnected, this, std::placeholders::_1, std::placeholders::_2), WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED); 
  WiFi.onEvent(std::bind(&MQTTSettingsService::onStationModeGotIP, this, std::placeholders::_1, std::placeholders::_2), WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
#endif

}

MQTTSettingsService::~MQTTSettingsService() {}

void MQTTSettingsService::begin() {
  SettingsService::begin();
}


void MQTTSettingsService::loop() {
  unsigned long currentMillis = millis();

  if (_reconfigureMQTT) {
    _reconfigureMQTT = false;
    _initialized = true;
    configureMQTT();
  }

  if (_mqtt.connected()) {
    _mqtt.loop();
  }

  if (_initialized && !_mqtt.connected() && (!_lastUpdate || (unsigned long)(currentMillis - _lastUpdate) >= MQTT_SETTINGS_MAX_CONNECTION_WAIT)) {
    if (_haveCredentials) {
      char usernameChar[_username.length()+1];
      _username.toCharArray(usernameChar, _username.length()+1);

      char passwordChar[_password.length()+1];
      _password.toCharArray(passwordChar, _password.length()+1);

      _mqtt.connect(MQTT_SETTINGS_CLIENT_NAME, usernameChar, passwordChar);

    } else {
      _mqtt.connect(MQTT_SETTINGS_CLIENT_NAME);
    }

    if (_mqtt.connected()) {
      Serial.println("Connected to MQTT server.");
    }
    _lastUpdate = currentMillis;
  }

}

void MQTTSettingsService::readFromJsonObject(JsonObject& root) {
  _hostname = root["hostname"] | MQTT_SETTINGS_SERVICE_DEFAULT_SERVER;
  _port = root["port"];
  _keepAlive = root["keepAlive"];

  _cleanSession = root["cleanSession"];
  _timeout = root["timeout"];
  _haveCredentials = root["haveCredentials"];
  _username = (String) root["username"].as<String>();
  _password = root["password"].as<String>();
  _base_topic = root["base_topic"].as<String>();

  _hostname.trim();
  if (!_hostname){
    _hostname = MQTT_SETTINGS_SERVICE_DEFAULT_SERVER;
  }

  if (_port < MQTT_SETTINGS_MIN_PORT){
    _port = MQTT_SETTINGS_MIN_PORT;
  } else if (_port > MQTT_SETTINGS_MAX_PORT) {
    _port = MQTT_SETTINGS_MAX_PORT;
  }
}

void MQTTSettingsService::writeToJsonObject(JsonObject& root) {
  root["hostname"] = _hostname;
  root["port"] = _port;
  root["keepAlive"] = _keepAlive;

  root["cleanSession"] = _cleanSession;
  root["timeout"] = _timeout;
  root["haveCredentials"] = _haveCredentials;
  root["username"] = _username;
  root["password"] = _password;
  root["base_topic"] = _base_topic;
}

void MQTTSettingsService::onConfigUpdated() {
  _reconfigureMQTT = true;
}

#if defined(ESP8266)
void MQTTSettingsService::onStationModeGotIP(const WiFiEventStationModeGotIP& event) {
  Serial.printf("Got IP address, starting MQTT\n");
  _reconfigureMQTT = true;
}

void MQTTSettingsService::onStationModeDisconnected(const WiFiEventStationModeDisconnected& event) {
  Serial.printf("WiFi connection dropped, stopping MQTT.\n");
  _reconfigureMQTT = false;
  // NTP.stop();
}
#elif defined(ESP_PLATFORM)
void MQTTSettingsService::onStationModeGotIP(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.printf("Got IP address, starting MQTT\n");
  _reconfigureMQTT = true;
}

void MQTTSettingsService::onStationModeDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
  Serial.printf("WiFi connection dropped, stopping MQTT.\n");
  _reconfigureMQTT = false;
  // NTP.stop();
}
#endif

void MQTTSettingsService::configureMQTT() {  

  Serial.println("MQTT configuration...");

  char hostnameChar[_hostname.length()+1];
  _hostname.toCharArray(hostnameChar, _hostname.length()+1);

  _mqtt.begin(hostnameChar, _port, client);
  _mqtt.setOptions(_keepAlive, _cleanSession, _timeout);
}

void MQTTSettingsService::processSyncEvent() {
}
