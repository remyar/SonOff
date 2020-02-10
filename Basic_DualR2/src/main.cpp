#include "./Low-Level/board.h"
#include "./WiFi/wifi.h"
#include "./mqtt/mqtt.h"
#include "./led/led.h"
#include "./relay/relay.h"
#include "./keyboard/keyboard.h"


void setup() {
    BOARD_Init();

    RELAI_TaskInit();

    KEYBOARD_TaskInit();
    MQTT_TaskInit();
    LED_TaskInit();
    WIFI_TaskInit();

}


void loop() {
    KEYBOARD_TaskRun();
    WIFI_TaskRun();
    MQTT_TaskRun();
    LED_TaskRun();
    RELAI_TaskRun();
}