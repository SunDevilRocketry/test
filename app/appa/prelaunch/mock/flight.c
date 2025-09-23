#include "main.h"
#include "led.h"
#include "usb.h"
#include "math.h"
#include "sensor.h"
#include "buzzer.h"
#include "common.h"
#include "ignition.h"

void flight_loop
(
    uint8_t* gps_mesg_byte,
    FLASH_STATUS* flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address,
    SENSOR_STATUS* sensor_status
)
{
}

void flight_calib
(
    uint8_t* gps_mesg_byte,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address
)
{
}

void flight_launch_detect
(
    uint32_t* launch_detect_start_time,
    SENSOR_STATUS* sensor_status,
    FLASH_STATUS* flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address
)
{
}

void flight_in_flight
(
    uint32_t* launch_detect_start_time,
    SENSOR_STATUS* sensor_status,
    FLASH_STATUS* flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address
)
{
}

void flight_deploy
(
    void
)
{
}

void flight_descent
(
    uint32_t* launch_detect_start_time,
    SENSOR_STATUS* sensor_status,
    FLASH_STATUS* flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address
)
{
}

void pid_loop
(
    void
)
{
}

float pid_control
(
    float current_input,
    float target,
    float dtime
)
{
    return 0.0f;
}

void v_pid_function
(
    PID_DATA* pid_data, 
    float velocity
)
{
}
