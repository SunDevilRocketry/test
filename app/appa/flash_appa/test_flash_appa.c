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
extern FLASH_STATUS flash_read_return;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Procedures: Test Helpers
------------------------------------------------------------------------------*/
static PRESET_DATA get_default_configs
	(
	void
	) 
{
PRESET_DATA to_return;
memset(&to_return, 0, sizeof( PRESET_DATA ));
to_return.config_settings.enabled_features = 0b11100001; /* launch detect, dual deploy, data logging */
to_return.config_settings.enabled_data = 0b11111111; 	   /* all data enabled */
to_return.config_settings.sensor_calibration_samples = 1000;		/* unitless */
to_return.config_settings.launch_detect_timeout 	   = 30000; 		/* unit: ms */
to_return.config_settings.launch_detect_accel_threshold = 2;		/* unit: g	*/
to_return.config_settings.launch_detect_accel_samples	  = 5;		/* unitless */
to_return.config_settings.launch_detect_baro_threshold  = 300;	/* unit: Pa */
to_return.config_settings.launch_detect_baro_samples	  = 5;		/* unitless */
to_return.config_settings.control_delay_after_launch	  = 4000;	/* unit: ms */
to_return.config_settings.roll_control_constant_p = 0.0f; /* active control disabled */
to_return.config_settings.roll_control_constant_i = 0.0f; /* active control disabled */
to_return.config_settings.roll_control_constant_d = 0.0f; /* active control disabled */
to_return.config_settings.pitch_yaw_control_constant_p = 0.0f; /* active control disabled */
to_return.config_settings.pitch_yaw_control_constant_i = 0.0f; /* active control disabled */
to_return.config_settings.pitch_yaw_control_constant_d = 0.0f; /* active control disabled */
to_return.config_settings.control_max_deflection_angle = 0;	/* active control disabled */
to_return.config_settings.minimum_time_for_frame = 0;			/* unit: ms */
return to_return;
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
struct test_case
	{
	const char* description;
	bool is_preset_stored;
	FLASH_STATUS expected_return;
	FLASH_STATUS flash_read_return;
	};

struct test_case cases[] = 
	{
		{ "Read preset with existing preset data", true, FLASH_OK, FLASH_OK },
		{ "Read preset with no existing preset data", false, FLASH_PRESET_NOT_FOUND, FLASH_OK },
		{ "Error: flash fail", false, FLASH_FAIL, FLASH_FAIL },
	};

for( uint8_t test_num = 0; test_num < sizeof(cases) / sizeof(struct test_case); test_num++ )
	{
	TEST_begin_nested_case( cases[test_num].description );
	/*------------------------------------------------------------------------------
	Local variables
	------------------------------------------------------------------------------*/
	reset_stubs();
	reset_mock_flash();

	flash_read_return = cases[test_num].flash_read_return;
	HFLASH_BUFFER flash_handle;
	uint32_t address;

	/*------------------------------------------------------------------------------
	Call FUT
	------------------------------------------------------------------------------*/
	FLASH_STATUS result = read_preset
		(
		&flash_handle,
		&preset_data,
		&address
		);


	/*------------------------------------------------------------------------------
	Verify results
	------------------------------------------------------------------------------*/
	// TEST_ASSERT_EQ_MEMORY( "Read preset correctly loads the config preset", &mock_flash_memory[0], flash_handle.pbuffer, sizeof( PRESET_DATA ) );
	// TEST_ASSERT_EQ_UINT("Test for expected return value", result, cases[test_num].expected_return);

	TEST_end_nested_case();
	}
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
FLASH_STATUS result = write_preset
	(
	&flash_handle,
	&preset_data,
	&address
	);


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/
TEST_ASSERT_EQ_UINT("Test that write_preset returns FLASH_OK", result, FLASH_OK);

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
reset_stubs();
reset_mock_flash();

HFLASH_BUFFER flash_handle;
uint32_t address;

/* Load some stuff into flash memory */
preset_data = get_default_configs();

/* Save bit */
mock_flash_memory[0] = 1;
mock_flash_memory[1] = 0;
memcpy( &mock_flash_memory[2], &preset_data, sizeof( PRESET_DATA ));
/* Set another random part of memory to something */
memset( &mock_flash_memory[300], 1, 1 );

//bool memory_nonzero = false; // rename
for ( uint32_t i = sizeof( PRESET_DATA ) + 2; i < FLASH_MEMORY_SIZE; i++ )
	{
	if ( mock_flash_memory[i] != FLASH_ERASE_VALUE )
		{
		//memory_nonzero = true;
		printf("Unequal at %d: %d\n", i, mock_flash_memory[i]);
		}
	}

printf("\n--------------");

/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
FLASH_STATUS result = flash_erase_preserve_preset
	(
	&flash_handle,
	&address
	);


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/
bool memory_nonzero = false; // rename
for ( uint32_t i = sizeof( PRESET_DATA ) + 2; i < FLASH_MEMORY_SIZE; i++ )
	{
	if ( mock_flash_memory[i] != FLASH_ERASE_VALUE )
		{
		memory_nonzero = true;
		printf("Unequal at %d: %d\n", i, mock_flash_memory[i]);
		}
	}

printf("Return: %d\n", result);
// TEST_ASSERT_EQ_UINT( "Test that the rest of the memory was cleared", memory_nonzero, false);

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
reset_mock_flash();

/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
	{
	{ "Write Preset Test", test_write_preset },
	{ "Read Preset Test", test_read_preset },
	{ "Store Frame Test", test_store_frame },
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