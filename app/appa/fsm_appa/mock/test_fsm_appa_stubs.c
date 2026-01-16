/*******************************************************************************
*
* FILE:
*      test_fsm_appa_stubs.c
*
* DESCRIPTION:
*      Minimal stubs and helpers for APPA FSM unit tests.
*
*******************************************************************************/

#include <stdint.h>


/* HAL UID stubs for unit tests (static to avoid linkage conflicts) */
static uint32_t HAL_GetUIDw0(void) { return 0u; }
static uint32_t HAL_GetUIDw1(void) { return 0u; }
static uint32_t HAL_GetUIDw2(void) { return 0u; }

#include <stddef.h>
#include <string.h>
#include "buzzer.h"
#include "common.h"
#include "main.h"
#include "led.h"
#include "servo.h"
#include "sensor.h"
#include "usb.h"
#include "flash.h"
#include "test_fsm_appa_stubs.h"


/*------------------------------------------------------------------------------
Globals
------------------------------------------------------------------------------*/

//extern FLIGHT_COMP_STATE_TYPE flight_computer_state;

/* Error callback used by tests to intercept error_fail_fast */
void ( *error_callback )( ERROR_CODE ) = NULL;

/* Simple counters / flags for assertions in test_fsm_appa.c */
uint8_t stub_led_set_color_calls         = 0;
uint8_t stub_buzzer_multi_beeps_calls    = 0;
uint8_t stub_buzzer_beep_calls           = 0;
uint8_t stub_sensor_start_IT_calls       = 0;

bool    stub_prelaunch_called            = false;
bool    stub_flight_calib_called         = false;
bool    stub_flight_launch_detect_called = false;
bool    stub_flight_in_flight_called     = false;
bool    stub_flight_deploy_called        = false;
bool    stub_flight_descent_called       = false;

/* USB status for prelaunch_terminal */
USB_STATUS stub_usb_status_return        = USB_OK;

/* Sensor behavior */
SENSOR_STATUS sensor_status_return       = SENSOR_OK;

/* Servo angles used for simple motor_drive verification */
SERVO_PRESET servo_angles                = { 45, 45, 45, 45 };

/* Systick behavior */
uint32_t systick                         = 0;
uint32_t systick_calls                   = 0;

/* Flash behavior (for timeout / busy tests if needed later) */
uint16_t preset_preserving_flash_erase_calls = 0;
uint16_t flash_busy_calls                = 0;
uint16_t flash_busy_counts               = 0;

/* launch_detect/apogee flags (kept for consistency, but FSM tests do not rely heavily on them) */
bool ld_expected                         = false;
bool is_apogee_detected                  = false;

/* sensor_dump watchdog */
uint16_t sensor_dump_calls               = 0;

/* Controls how many iterations appa_fsm's while loop executes before forcing exit */
static uint8_t loop_iterations_before_exit = 0;
static uint8_t loop_iteration_counter      = 0;


/*------------------------------------------------------------------------------
Helpers
------------------------------------------------------------------------------*/

void stubs_reset
    (
    void
    )
{
error_callback                     = NULL;

stub_led_set_color_calls           = 0;
stub_buzzer_multi_beeps_calls      = 0;
stub_buzzer_beep_calls             = 0;
stub_sensor_start_IT_calls         = 0;

stub_prelaunch_called              = false;
stub_flight_calib_called           = false;
stub_flight_launch_detect_called   = false;
stub_flight_in_flight_called       = false;
stub_flight_deploy_called          = false;
stub_flight_descent_called         = false;

stub_usb_status_return             = USB_OK;

sensor_status_return               = SENSOR_OK;

servo_angles.rp_servo1             = 45;
servo_angles.rp_servo2             = 45;
servo_angles.rp_servo3             = 45;
servo_angles.rp_servo4             = 45;

systick                            = 0;
systick_calls                      = 0;

preset_preserving_flash_erase_calls= 0;
flash_busy_calls                   = 0;
flash_busy_counts                  = 0;

ld_expected                        = false;
is_apogee_detected                 = false;

sensor_dump_calls                  = 0;

loop_iterations_before_exit        = 0;
loop_iteration_counter             = 0;
}


void set_error_callback
    (
    void ( *input_callback )( ERROR_CODE )
    )
{
error_callback = input_callback;
}


void set_return_launch_detection
    (
    bool expected
    )
{
ld_expected = expected;
}


void set_return_HAL_GetTick
    (
    uint32_t ret
    )
{
systick = ret;
}


SERVO_PRESET get_servo_angles_struct
    (
    void
    )
{
return servo_angles;
}


void set_loop_exit_after_n_iterations
    (
    uint8_t n
    )
{
loop_iterations_before_exit = n;
loop_iteration_counter      = 0;
}


/*------------------------------------------------------------------------------
Core stubs used by FSM
------------------------------------------------------------------------------*/

void error_fail_fast
    (
    volatile ERROR_CODE error_code
    )
{
if( error_callback != NULL )
    {
    error_callback( error_code );
    }
}


void led_set_color
    (
    LED_COLOR_CODES color
    )
{
(void)color;
stub_led_set_color_calls++;
}


BUZZ_STATUS buzzer_beep
    (
    uint32_t duration
    )
{
(void)duration;
stub_buzzer_beep_calls++;
return BUZZ_OK;
}


BUZZ_STATUS buzzer_multi_beeps
    (
    uint32_t beep_duration,
    uint32_t time_between_beeps,
    uint8_t  num_beeps
    )
{
(void)beep_duration;
(void)time_between_beeps;
(void)num_beeps;
stub_buzzer_multi_beeps_calls++;
return BUZZ_OK;
}


SENSOR_STATUS sensor_start_IT
    (
    SENSOR_DATA* sensor_data_ptr
    )
{
(void)sensor_data_ptr;
stub_sensor_start_IT_calls++;
return sensor_status_return;
}


void motor_drive
    (
    SERVO_ID servo,
    uint8_t  angle
    )
{
switch( servo )
    {
    case SERVO_1:
        servo_angles.rp_servo1 = angle;
        break;
    case SERVO_2:
        servo_angles.rp_servo2 = angle;
        break;
    case SERVO_3:
        servo_angles.rp_servo3 = angle;
        break;
    case SERVO_4:
        servo_angles.rp_servo4 = angle;
        break;
    default:
        break;
    }
}


uint32_t HAL_GetTick
    (
    void
    )
{
systick_calls++;
return systick;
}


/* Dump all sensor readings to console; used as a generic periodic action */
SENSOR_STATUS sensor_dump
    (
    SENSOR_DATA* sensor_data_ptr
    )
{
(void)sensor_data_ptr;
sensor_dump_calls++;

/* Safety net: break potential infinite loops by forcing IDLE */
if( sensor_dump_calls > 20 )
    {
    fc_state_update ( FC_STATE_IDLE );
    }

return sensor_status_return;
}


/* Flash helpers (minimal, in case FSM interacts via flight_* wrappers) */
bool flash_is_flash_busy
    (
    void
    )
{
if( flash_busy_counts == 0 ||
    flash_busy_calls % ( flash_busy_counts + 1 ) == flash_busy_counts )
    {
    flash_busy_calls++;
    return false;
    }
else
    {
    flash_busy_calls++;
    return true;
    }
}


FLASH_STATUS flash_erase_preserve_preset
    (
    HFLASH_BUFFER* pflash_handle,
    uint32_t*      address
    )
{
(void)pflash_handle;
(void)address;
preset_preserving_flash_erase_calls++;
return FLASH_OK;
}


/*------------------------------------------------------------------------------
FSM-specific collaborators
------------------------------------------------------------------------------*/

/* prelaunch.c: function called by appa_fsm in IDLE */
USB_STATUS prelaunch_terminal
    (
    uint8_t        firmware_code,
    FLASH_STATUS*  flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t*      flash_address,
    uint8_t*       gps_mesg_byte,
    SENSOR_STATUS* sensor_status
    )
{
(void)firmware_code;
(void)flash_status;
(void)flash_handle;
(void)flash_address;
(void)gps_mesg_byte;
(void)sensor_status;

stub_prelaunch_called = true;

/* Loop exit management: after N iterations, push state beyond FC_STATE_MAX */
if( loop_iterations_before_exit > 0 )
    {
    loop_iteration_counter++;
    if( loop_iteration_counter >= loop_iterations_before_exit )
        {
        fc_state_update ( FC_STATE_MAX + 1 );
        }
    }

return stub_usb_status_return;
}


/* flight.c high-level state handlers, observed by tests via flags */

void flight_calib
    (
    uint8_t*       gps_mesg_byte,
    HFLASH_BUFFER* flash_handle,
    uint32_t*      flash_address
    )
{
(void)gps_mesg_byte;
(void)flash_handle;
(void)flash_address;
stub_flight_calib_called = true;
}


void flight_launch_detect
    (
    uint32_t*      ld_start_time,
    SENSOR_STATUS* sensor_status,
    FLASH_STATUS*  flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t*      flash_address
    )
{
(void)ld_start_time;
(void)sensor_status;
(void)flash_status;
(void)flash_handle;
(void)flash_address;
stub_flight_launch_detect_called = true;
}


void flight_in_flight
    (
    uint32_t*      ld_start_time,
    SENSOR_STATUS* sensor_status,
    FLASH_STATUS*  flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t*      flash_address
    )
{
(void)ld_start_time;
(void)sensor_status;
(void)flash_status;
(void)flash_handle;
(void)flash_address;
stub_flight_in_flight_called = true;
}


void flight_deploy
    (
    void
    )
{
stub_flight_deploy_called = true;
}


void flight_descent
    (
    uint32_t*      ld_start_time,
    SENSOR_STATUS* sensor_status,
    FLASH_STATUS*  flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t*      flash_address
    )
{
(void)ld_start_time;
(void)sensor_status;
(void)flash_status;
(void)flash_handle;
(void)flash_address;
stub_flight_descent_called = true;
}
