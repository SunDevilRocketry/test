/*******************************************************************************
*
* FILE: 
*      led.h (MOCK)
*
* DESCRIPTION: 
*      Header file to trick the test into compiling. Also contains mock
*      definitions.
*
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#define LED_YELLOW 0
#define LED_GREEN 1
#define LED_WHITE 2
#define LED_RED 3
#define LED_CYAN 4
#define LED_PURPLE 5
#define LED_BLUE 6

#define CONNECT_OP 0
#define SENSOR_OP 1
#define FIN_OP 2
#define FLASH_OP 3
#define PRESET_OP 4

void led_set_color(int color) {

}

void buzzer_beep(int var0) {

}

void buzzer_multi_beeps(int var0, int var2, int var3) {

}

bool usb_detect() {
    return true;
}

void ping () {

}

bool ign_switch_cont() {
    return true;
}

bool ign_drogue_cont() {
    return true;
}

bool ign_main_cont() {
    return true;
}
