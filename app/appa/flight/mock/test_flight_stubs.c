#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "buzzer.h"
#include "common.h"
#include "main.h"
#include "led.h"
#include "servo.h"
#include "sensor.h"
#include "usb.h"
#include "ignition.h"
#include "gps.h"
#include "flash.h"

/* globals */
bool was_gps_enabled = false;
IGN_STATUS ign_main_status[3] = { IGN_OK, IGN_OK, IGN_OK };
uint8_t ign_main_call_num = 0;
IGN_STATUS ign_drogue_status[3] = { IGN_OK, IGN_OK, IGN_OK };
uint8_t ign_drogue_call_num = 0;

/* internal use */

void stubs_reset
	(
	void
	)
{
was_gps_enabled = false;
memset( ign_main_status, IGN_OK, 3 * sizeof( IGN_STATUS ) );
ign_main_call_num = 0;
ign_drogue_call_num = 0;
}

void set_return_ign_deploy_main
	(
	IGN_STATUS new_status[3]
	)
{
memcpy( ign_main_status, new_status, 3 * sizeof( IGN_STATUS ) );
}

void set_return_ign_deploy_drogue
	(
	IGN_STATUS new_status[3]
	)
{
memcpy( ign_drogue_status, new_status, 3 * sizeof( IGN_STATUS ) );
}

unsigned int get_num_calls_ign_deploy_main()
	{
	return ign_main_call_num;
	}

unsigned int get_num_calls_ign_deploy_drogue()
	{
	return ign_drogue_call_num;
	}

void error_fail_fast
    (
    volatile ERROR_CODE error_code
    )
{

}

void led_set_color
	(
	LED_COLOR_CODES color
	)
{

}

void motor_drive(SERVO_ID servo, uint8_t angle)
{

}

uint8_t motor_snap_to_bound(uint8_t angle, uint8_t upper, uint8_t lower)
{
return angle;
}

uint32_t HAL_GetTick(void)
{
return 0;
}

GPS_STATUS gps_receive_IT
	(
	uint8_t*    rx_data_ptr , /* Buffer to export data to        */
	size_t   rx_data_size /* Size of the data to be received */
	)
{
was_gps_enabled = true;
return GPS_OK;
}

/* Beep the flight computer buzzer */
BUZZ_STATUS buzzer_beep
	(
	uint32_t duration /* Length of beep in milliseconds */
	)
{
return BUZZ_OK;
}

/* Beep the flight computer buzzer a specified number of times (blocking) */
BUZZ_STATUS buzzer_multi_beeps
	(
	uint32_t beep_duration, 		/* Length of beep in milliseconds */
	uint32_t time_between_beeps,	/* How long to wait between beeps in ms */
	uint8_t	 num_beeps 				/* How many times to repeat */
	)
{
return BUZZ_OK;
}

/* Beep the flight computer buzzer specified number of times */
BUZZ_STATUS buzzer_num_beeps
	(
	uint8_t num_beeps /* Number of beeps */
	)
{
return BUZZ_OK;
}

/* Dump all sensor readings to console */
SENSOR_STATUS sensor_dump
	(
    SENSOR_DATA* sensor_data_ptr 
    )
{
return SENSOR_OK;
}

/* Check if the flash chip is ready for write operations */
bool flash_is_flash_busy
	(
	void
	)
{
return false;
}

/* Asserts the ignition signal to ignite the main parachute deployment ematch. 
   Returns a response code indicating if the ignition occured succesfully */
IGN_STATUS ign_deploy_main 
    (
	void
    )
{
ign_main_call_num++;
return ign_main_status[ign_main_call_num - 1 < 3 ? ign_main_call_num - 1 : 0];
}


/* Asserts the ignition signal to ignite the drogue parachute deployment ematch. 
   Returns a response code indicating if the ignition occured succesfully */
IGN_STATUS ign_deploy_drogue 
    (
	void
    )
{
ign_drogue_call_num++;
return ign_drogue_status[ign_drogue_call_num - 1 < 3 ? ign_drogue_call_num - 1 : 0];
}


/* Returns TRUE if there is continuity across the main parachute deployment 
   ematch */
bool ign_main_cont
	(
	void
	)
{
return true;
}


/* Returns TRUE if there is continuity across the drogue parachute deployment 
   ematch */
bool ign_drogue_cont
	(
	void
	)
{
return true;
}

/* Returns TRUE if there is continuity across the switch screw terminals */
bool ign_switch_cont
	(
	void
	)
{
return true;
}

/*----------------------------------------------------------------------
 main.h
----------------------------------------------------------------------*/

/* apogee_detect.c */
bool apogee_detect
	(
	void
	)
{
return true;
}

/* fin_calib.c */
USB_STATUS finCalibration
	(
	uint8_t *signalIn
	)
{
return USB_OK;
}

/* flash_appa.c */
FLASH_STATUS store_frame 
	(
	HFLASH_BUFFER* pflash_handle,
	SENSOR_DATA*   sensor_data_ptr,
	uint32_t       time,
	uint32_t*	   address
	)
{
return FLASH_OK;
}

FLASH_STATUS read_preset
	(
	HFLASH_BUFFER* pflash_handle,
	PRESET_DATA*   preset_data_ptr,
	uint32_t*	   address
	)
{
return FLASH_OK;
}

FLASH_STATUS write_preset 
	(
	HFLASH_BUFFER* pflash_handle,
	PRESET_DATA*   preset_data_ptr,
	uint32_t* 	   address
	)
{
return FLASH_OK;
}

FLASH_STATUS flash_erase_preserve_preset
	(
	HFLASH_BUFFER* pflash_handle,
	uint32_t* address
	)
{
return FLASH_OK;
}

FLASH_STATUS get_sensor_frame
	(
	SENSOR_DATA* sensor_data_ptr, /* i: sensor data struct */
	uint8_t* buffer, /* o: sensor frame */
	uint32_t time 	 /* i: frame timestamp */
	)
{
return FLASH_OK;
}

void sensor_frame_size_init
	(
	void
	)
{

}

/* launch_detect.c */
void launch_detection()
{

}

/* flight.c */
// REMOVED. FUT.

/* prelaunch.c */
void pre_launch_loop
    (
    uint8_t firmware_code,
    FLASH_STATUS* flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address,
    uint8_t* gps_mesg_byte,
    SENSOR_STATUS* sensor_status
    )
{

}

FLASH_STATUS preset_cmd_execute
    ( 
    uint8_t* subcommand_code,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address
    )
{
return FLASH_OK;
}

bool check_config_validity
    ( 
    PRESET_DATA* preset_data_ptr 
    )
{
return true;
}

/* sensor_calibrate.c */
void sensorCalibrationSWCON(SENSOR_DATA* sensor_data_ptr)
{

}