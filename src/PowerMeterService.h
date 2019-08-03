#ifndef PowerMeterService_h
#define PowerMeterService_h

#include <Arduino.h>
#include "EmonLib.h"

#define ANALOG_INPUT_SENSOR1  A0
#define AC_VOLTAGE  220.0

class PowerMeterService {

  public:

    PowerMeterService();

    void begin();
    void loop();

  private:    
    unsigned long _lastUpdate;
    double kwh = 0;    
    bool _initialized = false;
};

#endif // end PowerMeterService_h