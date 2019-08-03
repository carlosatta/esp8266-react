#include <LCDService.h>

SH1106Wire display(0x3c, D2, D1);  // ADDRESS, SDA, SCL
OLEDDisplayUi ui     ( &display );

void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(120, 0, String(millis()));
}

void drawFrame1(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->drawXbm(x + 34, y + 14, robot_32x32_width, robot_32x32_height, robot_32x32_bits);
}

void drawFrame2(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0 + x, 10 + y, "Arial 10");

  display->setFont(ArialMT_Plain_16);
  display->drawString(0 + x, 20 + y, "Arial 16");

  display->setFont(ArialMT_Plain_24);
  display->drawString(0 + x, 34 + y, "Arial 24");
}

FrameCallback frames[] = { drawFrame1, drawFrame2 };

int frameCount = 2;

OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;


LCDService::LCDService() {}

void LCDService::begin() {
  Serial.println("Initializing OLED Display");
  display.init();
  display.clear();
  display.drawXbm(48, 0, robot_32x32_width, robot_32x32_height, robot_32x32_bits);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(11, 30, "Power-O-Meter");
  display.display();
}

void LCDService::loop() {

  if (_initialized == false) {
    display.clear();
    ui.setTargetFPS(60);

    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);

    ui.setIndicatorPosition(BOTTOM);
    
    ui.setIndicatorDirection(LEFT_RIGHT);

    ui.setFrameAnimation(SLIDE_LEFT);
    ui.setFrames(frames, frameCount);

    ui.setOverlays(overlays, overlaysCount);

    ui.init();
    _initialized = true;
  }

  int remainingTimeBudget = ui.update();

  if (remainingTimeBudget > 0) {
    delay(remainingTimeBudget);
  }

  // time_t timeNow = now();
  // timeStatus_t status = timeStatus();
  // Serial.println(status);

}



