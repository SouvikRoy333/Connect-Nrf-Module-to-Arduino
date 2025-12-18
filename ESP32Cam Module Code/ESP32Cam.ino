#include "esp_camera.h"

#include <WiFi.h>

//

// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality

//

Ensure ESP32 Wrover Module or other board with PSRAM is selected

//

Partial images will be transmitted if image exceeds buffer size

//

//

You must select partition scheme from the board menu that has at least 3MB APP space.

//

Face Recognition is DISABLED for ESP32 and ESP32-S2, because it takes up from 15

//

seconds to process single frame. Face Detection is ENABLED if PSRAM is enabled as well

//

// Select camera model

//

//#define CAMERA MODEL_WROVER_KIT // Has PSRAM

#define CAMERA_MODEL_ESP_EYE // Has PSRAM

//#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM

//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM

//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM

//#define CAMERA MODEL _M5STACK_WIDE // Has PSRAM

//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM

//#define CAMERA_MODEL_MSSTACK_UNITCAM // No PSRAM

//#define CAMERA_MODEL_AI_THINKER // Has PSRAM

//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
//#define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM

//#define CAMERA_MODEL_AI_THINKER // Has PSRAM

//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM

//#define CAMERA_MODEL_XIAO_ESP3253 // Has PSRAM

//** Espressif Internal Boards **

//#define CAMERA_MODEL_ESP32_CAM_BOARD

//#define CAMERA_MODEL_ESP3252_CAM_BOARD

//#define CAMERA MODEL ESP3253 CAM LCD

//#define CAMERA_MODEL_DFRobot_FireBeetle2_ESP3253 // Has PSRAM

//#define CAMERA_MODEL_DFRobot_Romeo_ESP3253 // Has PSRAM

#include "camera_pins.h"

11

// Enter your WiFi credentials

const char* ssid = "";

const char* password = "";

void startCameraServer();

void setupLedFlash(int pin);

void setup() {

Serial.begin(115200);

Serial.setDebugOutput(true);

Serial.println();

camera_config_t config;
