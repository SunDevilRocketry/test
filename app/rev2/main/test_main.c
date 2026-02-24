/*******************************************************************************
*
* FILE: 
*      test_main.c
*
* DESCRIPTION: 
*      Unit tests for the entry point procedure.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>


/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/

/* Application Layer */
#include "main.h"
#include "init.h"

/* Low-level modules */
#include "common.h"
#include "error_sdr.h"
#include "baro.h"
#include "buzzer.h"
#include "commands.h"
#include "flash.h"
#include "ignition.h"
#include "imu.h"
#include "led.h"
#include "sensor.h"
#include "servo.h"
#include "usb.h"
#include "gps.h"

/* Test */
#include "sdrtf_pub.h"
#include "test_main.h"

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
extern FLASH_STATUS flash_init_return;
extern BARO_STATUS baro_init_return;
extern IMU_STATUS imu_init_return;
extern SERVO_STATUS servo_init_return;
extern FLASH_STATUS read_preset_return;
extern ERROR_CODE last_error;
extern bool is_switch_toggled;

/*------------------------------------------------------------------------------
Local Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
External Declarations
------------------------------------------------------------------------------*/
extern int main_fut(void);  // main.c:main()

/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       main			                                   			       	   *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test main() in main.c												   *
*                                                                              *
*******************************************************************************/
void test_main
	(
	void
	) 
{

struct test_case 
	{
	const char* description;
	FLASH_STATUS flash_init;
	BARO_STATUS baro_init;
	IMU_STATUS imu_init;
	SERVO_STATUS servo_init;
	FLASH_STATUS read_preset;
	bool switch_continuity;
	ERROR_CODE expected_error;
	};
struct test_case cases[] =
	{
	{ "Normal Case: Initialization Correct", FLASH_OK, BARO_OK, IMU_OK, SERVO_OK, FLASH_OK, false, ERROR_NO_ERROR },
	{ "Robust Case: Flash Init Fail", FLASH_INIT_FAIL, BARO_OK, IMU_OK, SERVO_OK, FLASH_OK, false, ERROR_FLASH_INIT_ERROR },
	{ "Robust Case: Baro Init Fail", FLASH_OK, BARO_FAIL, IMU_OK, SERVO_OK, FLASH_OK, false, ERROR_BARO_INIT_ERROR },
	{ "Robust Case: IMU Init Fail", FLASH_OK, BARO_OK, IMU_FAIL, SERVO_OK, FLASH_OK, false, ERROR_IMU_INIT_ERROR },
	{ "Robust Case: Servo Init Fail", FLASH_OK, BARO_OK, IMU_OK, SERVO_FAIL, FLASH_OK, false, ERROR_SERVO_INIT_ERROR },
	{ "Robust Case: Read Preset Fail", FLASH_OK, BARO_OK, IMU_OK, SERVO_OK, FLASH_FAIL, false, ERROR_FLASH_CMD_ERROR },
	{ "Robust Case: Switch Terminal Toggled", FLASH_OK, BARO_OK, IMU_OK, SERVO_OK, FLASH_OK, true, ERROR_DATA_HAZARD_ERROR }
	};

for( uint8_t test_num = 0; test_num < sizeof(cases) / sizeof(struct test_case); test_num++ )
	{
	/*------------------------------------------------------------------------------
	Set Up Test
	------------------------------------------------------------------------------*/
	TEST_begin_nested_case( cases[test_num].description );
	flash_init_return = cases[test_num].flash_init;
	baro_init_return = cases[test_num].baro_init;
	imu_init_return = cases[test_num].imu_init;
	servo_init_return = cases[test_num].servo_init;
	read_preset_return = cases[test_num].read_preset;
	is_switch_toggled = cases[test_num].switch_continuity;
	
	/*------------------------------------------------------------------------------
	Call FUT
	------------------------------------------------------------------------------*/
	main_fut();

	/*------------------------------------------------------------------------------
	Verify Results
	------------------------------------------------------------------------------*/
	TEST_ASSERT_EQ_UINT( "Test that the returned error code equals the expected.", last_error, cases[test_num].expected_error );

	TEST_end_nested_case();
	}
} /* test_main */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       main			                                   			       	   *
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
	{ "Test main()", test_main }
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "main.c", tests );

return 0;

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/