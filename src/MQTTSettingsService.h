#ifndef MQTTSettingsService_h
#define MQTTSettingsService_h

// #if defined(ESP8266)
//   #include <ESP8266WiFi.h>
// #elif defined(ESP_PLATFORM)
//   #include <WiFi.h>
// #endif

// #include <WiFiSettingsService.h>

#include <SettingsService.h>
#include <MQTT.h>

// default time server
#define MQTT_SETTINGS_SERVICE_DEFAULT_SERVER "192.168.1.1"
#define MQTT_SETTINGS_SERVICE_DEFAULT_PORT 8883

// min poll delay of 60 secs, max 1 day
#define MQTT_SETTINGS_MIN_PORT 1
#define MQTT_SETTINGS_MAX_PORT 86400

#define MQTT_SETTINGS_MAX_CONNECTION_WAIT 10000

#define MQTT_SETTINGS_CLIENT_NAME "power-o-meter"

#define MQTT_SETTINGS_FILE "/config/mqttSettings.json"
#define MQTT_SETTINGS_SERVICE_PATH "/rest/mqttSettings"

class MQTTSettingsService : public AdminSettingsService {

  public:

    MQTTSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager, MQTTClient* mqtt);
    ~MQTTSettingsService();

    void begin();
    void loop();

  protected:

    void readFromJsonObject(JsonObject& root);
    void writeToJsonObject(JsonObject& root);
    void onConfigUpdated();

  private:

    unsigned long _lastUpdate;

    bool _reconfigureMQTT;
    bool _initialized = false;
    

    String _hostname;
    int _port;
    int _keepAlive;
    bool _cleanSession;
    int _timeout;
    bool _haveCredentials;
    String _username;
    String _password;
    String _base_topic;

    MQTTClient _mqtt;
 

#if defined(ESP8266)
    WiFiEventHandler _onStationModeDisconnectedHandler;
    WiFiEventHandler _onStationModeGotIPHandler;

    void onStationModeGotIP(const WiFiEventStationModeGotIP& event);
    void onStationModeDisconnected(const WiFiEventStationModeDisconnected& event);
#elif defined(ESP_PLATFORM)
    void onStationModeGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
    void onStationModeDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
#endif

    void configureMQTT();
    void processSyncEvent();

};

#endif // end MQTTSettingsService_h
