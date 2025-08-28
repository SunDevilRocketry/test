/*******************************************************************************
*
* FILE: 
*      test_flight.c
*
* DESCRIPTION: 
*      Unit tests for functions in the flight module.
*
* NOTE: 
*	   This is pasted from a template. Take a look at some other tests to find 
*	   more examples.
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
#include "sdrtf_pub.h"
#include "main.h"
#include "sensor.h"
#include "servo.h"
#include "ignition.h"
#include "flash.h"
#include "test_flight_stubs.h"

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
uint8_t sensor_frame_size;
uint32_t tdelta;
SENSOR_DATA sensor_data;
SERVO_PRESET servo_preset;
PRESET_DATA preset_data;
FLIGHT_COMP_STATE_TYPE flight_computer_state;
PID_DATA pid_data;

/* Test-only globals */
extern bool was_gps_enabled;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Procedures: Test Helpers
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_flight_calib		  				                           	   *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test calibration state												   *
*                                                                              *
*******************************************************************************/
void test_flight_calib
	(
	void
	)
{
/*------------------------------------------------------------------------------
Set up mocks/stubs
------------------------------------------------------------------------------*/
stubs_reset();
uint8_t gps_mesg_byte[1];
HFLASH_BUFFER flash_handle[1];
uint32_t flash_address_ptr[1];
preset_data.config_settings.enabled_features = 255u;

/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
flight_calib
	(
	gps_mesg_byte,
    flash_handle,
    flash_address_ptr
	);

/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/
/* The only critical parts of this are GPS enablement based on feature flags. All
   others can be proven by analysis. */
TEST_ASSERT_EQ_UINT("Test that GPS was enabled.", was_gps_enabled, true);

} /* test_flight_calib */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_flight_deploy		  				                           	   *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test deployment state												   *
*                                                                              *
*******************************************************************************/
void test_flight_deploy
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
	IGN_STATUS drogue_status_returns[3];
	IGN_STATUS main_status_returns[3];
	uint8_t exp_num_attempts_needed_main;
	uint8_t exp_num_attempts_needed_drogue;
	};
struct test_case cases[] =
	{
		{ "Immediate Success", { IGN_SUCCESS, IGN_SUCCESS, IGN_SUCCESS }, { IGN_SUCCESS, IGN_SUCCESS, IGN_SUCCESS }, 1, 1 },
		{ "First Fail", { IGN_SUCCESS, IGN_SUCCESS, IGN_SUCCESS }, { IGN_MAIN_FAIL, IGN_SUCCESS, IGN_SUCCESS }, 2, 2 },
		{ "Two Fails", { IGN_DROGUE_FAIL, IGN_DROGUE_FAIL, IGN_SUCCESS }, { IGN_MAIN_FAIL, IGN_SUCCESS, IGN_SUCCESS }, 3, 3 }
	};
for( uint8_t test_num = 0; test_num < sizeof(cases) / sizeof(struct test_case); test_num++ )
	{
	TEST_begin_nested_case( cases[test_num].description );

	/*------------------------------------------------------------------------------
	Set up mocks/stubs
	------------------------------------------------------------------------------*/
	stubs_reset();
	set_return_ign_deploy_drogue(cases[test_num].drogue_status_returns);
	set_return_ign_deploy_main(cases[test_num].main_status_returns);

	/*------------------------------------------------------------------------------
	Call FUT
	------------------------------------------------------------------------------*/
	flight_deploy();

	/*------------------------------------------------------------------------------
	Verify results
	------------------------------------------------------------------------------*/
	/* The only critical parts of this are GPS enablement based on feature flags. All
	others can be proven by analysis. */
	TEST_ASSERT_EQ_UINT("Test that main chute deployment was called the right number of times.", get_num_calls_ign_deploy_main(), cases[test_num].exp_num_attempts_needed_main);
	TEST_ASSERT_EQ_UINT("Test that drogue chute deployment was called the right number of times.", get_num_calls_ign_deploy_drogue(), cases[test_num].exp_num_attempts_needed_drogue);

	TEST_end_nested_case();
	}

} /* test_flight_deploy */


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
/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
	{
	{ "Sensor Calibration", test_flight_calib },
	{ "Chute Deployment", test_flight_deploy }
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "flight", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/