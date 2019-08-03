#ifndef LCDService_h
#define LCDService_h

#include <Arduino.h>
#include <IPAddress.h>
#include <NTPStatus.h>
#include "SH1106Wire.h"
#include "OLEDDisplayUi.h"

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP_PLATFORM)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include "icons.h"
#include "symbols.h"

class LCDService {

  public:

    LCDService();

    void begin();
    void loop();

  private:
    unsigned long _lastUpdate;
    bool _initialized = false;
};

#endif // end LCDService_h