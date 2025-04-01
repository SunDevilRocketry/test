/*******************************************************************************
*
* FILE: 
*      test_launch_detect.c
*
* DESCRIPTION: 
*      Unit tests for the launch detect functionality in Canard.
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
#include "unity.h"
#include "main.h"
#include "sensor.h"
#include "imu.h"

/* unity.h is required for all unit tests. Other headers should be added if they
   are relevant to the test. */

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart4;  /* GPS */
I2C_HandleTypeDef  hi2c1;   /* Baro sensor    */
I2C_HandleTypeDef  hi2c2;   /* IMU and GPS    */
SENSOR_DATA sensor_data;
BARO_PRESET baro_preset;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/
#define EXPECTED_COVERAGE 100 /* set this to 100 to specify full coverage */

/*------------------------------------------------------------------------------
Procedures: Test Helpers // Any misc functions that need to be called by tests
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       foo	          	                                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Example helper function for test								       *
*                                                                              *
*******************************************************************************/
int foo(int input) {
	return input + 1;
} /* foo */


/*------------------------------------------------------------------------------
Procedures: Unity Functions // Even if they're empty, these have to be here
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       setUp                                                                  *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Code to run prior to any test                                          *
*                                                                              *
*******************************************************************************/
void setUp
	(
	void
    )
{
} /* setUp */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       tearDown                                                               *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Code to run after tests                                                *
*                                                                              *
*******************************************************************************/
void tearDown 
	(
	void
    )
{
} /* tearDown */


/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_acc_launch_detection		  			                           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the launch detection function in Canard.						   *
*                                                                              *
*******************************************************************************/
void test_launch_detection 
	(
	void
    )
{
/* Step: Set up test */
#define NUM_CASES_LAUNCH_DETECT 10
#define NUM_EXPECTED_SAMPLES 11
printf("\nUnit Tests: test_launch_detect\n");

uint8_t acc_detect_flag = 0;

/* Step: Set up test vectors (inputs, expected) */
int inputsAcc[NUM_CASES_LAUNCH_DETECT][NUM_EXPECTED_SAMPLES] = 
{
#include "cases/acc_inputs.txt"
};

int inputsBaro[NUM_CASES_LAUNCH_DETECT][NUM_EXPECTED_SAMPLES] = 
{
#include "cases/baro_inputs.txt"
};

int expected[NUM_CASES_LAUNCH_DETECT][NUM_EXPECTED_SAMPLES] = 
{
#include "cases/launch_detect_expected.txt"
};

/* Step: Execute tests */
for ( int test_num = 0; test_num < NUM_CASES_LAUNCH_DETECT; test_num++ )
	{
	for ( int i = 0; i < NUM_EXPECTED_SAMPLES; i++ )
		{
			sensor_data.imu_data.imu_converted.accel_x = inputsAcc[test_num][i];
			sensor_data.imu_data.imu_converted.accel_y = inputsAcc[test_num][i];
			sensor_data.imu_data.imu_converted.accel_z = inputsAcc[test_num][i];
			sensor_data.baro_pressure = inputsBaro[test_num][i];
			launch_detection(&acc_detect_flag);
			TEST_ASSERT_EQUAL_INT(expected[test_num][i], acc_detect_flag);
			printf("\tlaunch_detect #%d-b%d passed\n", test_num + 1, i+1); // prints a 1-indexed number instead of 0-indexed
		}
	/* reset test */
	acc_detect_flag = 0;
	sensor_data.imu_data.imu_converted.accel_x = 0;
	sensor_data.imu_data.imu_converted.accel_y = 0;
	sensor_data.imu_data.imu_converted.accel_z = 0;
	sensor_data.baro_pressure = 0;
	launch_detection(&acc_detect_flag);
	}

} /* test_launch_detect */


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
UNITY_BEGIN();
printf("-------------------------------------------------\n");
printf("	Launch Detect UNIT TESTING\n");
printf("-------------------------------------------------\n");
printf("\nNote: These unit tests exit on a failed assert. If the test fails, go to the case after the last pass.\n");

// List test functions here.
RUN_TEST( test_launch_detection );

if (EXPECTED_COVERAGE == 100) {
	printf("\nThis test suite expects full coverage (100%%).\n");
}
else {
	printf("\nThis test does not expect full coverage (> 100%%)\n");
}

return UNITY_END();
} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/