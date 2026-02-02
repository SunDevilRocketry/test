#ifndef TEST_FSM_APPA_STUBS_H /* recursive inclusion guard */
#define TEST_FSM_APPA_STUBS_H

#include <stdint.h>
#include "common.h"
#include "servo.h"
#include "sensor.h"
#include "usb.h"
#include "flash.h"
#include "error_sdr.h"


/* globals */
extern uint8_t stub_led_set_color_calls;
extern uint8_t stub_buzzer_multi_beeps_calls;
extern uint8_t stub_buzzer_beep_calls;
extern uint8_t stub_sensor_start_IT_calls;

extern bool    stub_prelaunch_called;
extern bool    stub_flight_calib_called;
extern bool    stub_flight_launch_detect_called;
extern bool    stub_flight_in_flight_called;
extern bool    stub_flight_deploy_called;
extern bool    stub_flight_descent_called;

extern USB_STATUS   stub_usb_status_return;
extern SENSOR_STATUS sensor_status_return;

extern SERVO_PRESET servo_angles;

extern uint32_t systick;
extern uint32_t systick_calls;

extern uint16_t preset_preserving_flash_erase_calls;
extern uint16_t flash_busy_calls;
extern uint16_t flash_busy_counts;

extern bool ld_expected;
extern bool is_apogee_detected;
extern uint16_t sensor_dump_calls;

/* functions */
void stubs_reset
    (
    void
    );

void set_error_callback
    (
    void ( *input_callback )( ERROR_CODE )
    );

void set_return_launch_detection
    (
    bool expected
    );

void set_return_HAL_GetTick
    (
    uint32_t ret
    );

SERVO_PRESET get_servo_angles_struct
    (
    void
    );

void set_loop_exit_after_n_iterations
    (
    uint8_t n
    );

#endif /* TEST_FSM_APPA_STUBS_H */
