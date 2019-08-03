#include <PowerMeterService.h>

EnergyMonitor emon1;

PowerMeterService::PowerMeterService() {}

void PowerMeterService::begin() {
  emon1.current(ANALOG_INPUT_SENSOR1, 40.909 ); // Current: input pin, calibration.
}

void PowerMeterService::loop() {
  unsigned long currentMillis = millis();

  if (!_lastUpdate || (unsigned long)(currentMillis - _lastUpdate) >= 1000) {    
     double Irms = emon1.calcIrms(1480);
     _lastUpdate = currentMillis;
  }
  
}
