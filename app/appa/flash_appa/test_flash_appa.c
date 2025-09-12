/*******************************************************************************
*
* FILE: 
*      test_flash_appa.c
*
* DESCRIPTION: 
*      Unit tests for functions in flash_appa.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "main.h"
#include "usb.h"
#include "string.h"
#include "led.h"
#include "imu.h"
#include "sdr_error.h"
#include "buzzer.h"
#include "flash.h"
#include "sensor.h"
#include "test_flash_appa_stubs.h"
#include "sdrtf_pub.h"

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
IMU_OFFSET imu_offset;
BARO_PRESET baro_preset;
SENSOR_DATA sensor_data;
PRESET_DATA preset_data;
CONFIG_SETTINGS_TYPE config_settings;
FLIGHT_COMP_STATE_TYPE flight_computer_state;
float feedback;

extern uint8_t sensor_frame_size;

/* Test-only globals */
extern uint8_t mock_flash_memory[FLASH_MEMORY_SIZE];
extern uint16_t flash_busy_calls;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Procedures: Test Helpers
------------------------------------------------------------------------------*/
static void make_default_configs
	(
	PRESET_DATA* preset_data_ptr
	) 
{
preset_data_ptr->config_settings.enabled_features = 0b11100001; /* launch detect, dual deploy, data logging */
preset_data_ptr->config_settings.enabled_data = 0b11111111; 	   /* all data enabled */
preset_data_ptr->config_settings.sensor_calibration_samples = 1000;		/* unitless */
preset_data_ptr->config_settings.launch_detect_timeout 	   = 30000; 		/* unit: ms */
preset_data_ptr->config_settings.launch_detect_accel_threshold = 2;		/* unit: g	*/
preset_data_ptr->config_settings.launch_detect_accel_samples	  = 5;		/* unitless */
preset_data_ptr->config_settings.launch_detect_baro_threshold  = 300;	/* unit: Pa */
preset_data_ptr->config_settings.launch_detect_baro_samples	  = 5;		/* unitless */
preset_data_ptr->config_settings.control_delay_after_launch	  = 4000;	/* unit: ms */
preset_data_ptr->config_settings.roll_control_constant_p = 0.0f; /* active control disabled */
preset_data_ptr->config_settings.roll_control_constant_i = 0.0f; /* active control disabled */
preset_data_ptr->config_settings.roll_control_constant_d = 0.0f; /* active control disabled */
preset_data_ptr->config_settings.pitch_yaw_control_constant_p = 0.0f; /* active control disabled */
preset_data_ptr->config_settings.pitch_yaw_control_constant_i = 0.0f; /* active control disabled */
preset_data_ptr->config_settings.pitch_yaw_control_constant_d = 0.0f; /* active control disabled */
preset_data_ptr->config_settings.control_max_deflection_angle = 0;	/* active control disabled */
preset_data_ptr->config_settings.minimum_time_for_frame = 0;			/* unit: ms */
}


/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_store_frame                                  			           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test store frame 													   *
*                                                                              *
*******************************************************************************/
void test_store_frame
	(
	void
	)
{
/* This is full coverage, but doesn't test anything yet */
/* Almost full drive-by coverage of sensor_frame_size_init and get_sensor_frame */
/*------------------------------------------------------------------------------
Cases
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Local variables
------------------------------------------------------------------------------*/
HFLASH_BUFFER flash_handle;
uint32_t time = 0;
uint32_t address;

reset_stubs();

/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
store_frame 
	(
	&flash_handle,
	&sensor_data,
	time,
	&address
	);


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/

} /* test_store_frame */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_read_preset                                  			           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test read preset 													   *
*                                                                              *
*******************************************************************************/
void test_read_preset
	(
	void
	)
{
/*------------------------------------------------------------------------------
Cases
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Local variables
------------------------------------------------------------------------------*/
HFLASH_BUFFER flash_handle;
uint32_t address;

reset_stubs();

/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
read_preset
	(
	&flash_handle,
	&preset_data,
	&address
	);


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/
TEST_ASSERT_EQ_MEMORY( "Read preset correctly places the preset into the flash handle", &mock_flash_memory, flash_handle.pbuffer, sizeof( PRESET_DATA ) );

} /* test_read_preset */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_write_preset                               			           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test write preset       											   *
*                                                                              *
*******************************************************************************/
void test_write_preset
	(
	void
	)
{
/*------------------------------------------------------------------------------
Cases
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Local variables
------------------------------------------------------------------------------*/
HFLASH_BUFFER flash_handle;
uint32_t address;


/*------------------------------------------------------------------------------
Set up mocks/stubs
------------------------------------------------------------------------------*/
reset_stubs();

/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
write_preset
	(
	&flash_handle,
	&preset_data,
	&address
	);


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/

} /* test_write_preset */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_flash_erase_preserve_preset                   		               *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test flash erase preserve preset   									   *
*                                                                              *
*******************************************************************************/
void test_flash_erase_preserve_preset
	(
	void
	)
{
/*------------------------------------------------------------------------------
Cases
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Local variables
------------------------------------------------------------------------------*/
HFLASH_BUFFER flash_handle;
uint32_t address;

reset_stubs();

/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
flash_erase_preserve_preset
	(
	&flash_handle,
	&address
	);


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/

} /* test_flash_erase_preserve_preset */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       main			                                   			           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Set up the testing enviroment, call tests, tear down the testing       *
*		environment															   *
*                                                                              *
*******************************************************************************/
int main
	(
	void
	)
{
memset( &mock_flash_memory, 0, FLASH_MEMORY_SIZE );

/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
	{
	{ "Read Preset Test", test_read_preset },
	{ "Store Frame Test", test_store_frame },
	{ "Read Preset Test", test_write_preset },
	{ "Flash Erase Preserve Preset Test", test_flash_erase_preserve_preset },
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "flash_appa", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/