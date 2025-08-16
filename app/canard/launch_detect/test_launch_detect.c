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
#include "sdrtf_pub.h"
#include "main.h"
#include "sensor.h"
#include "imu.h"

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
			TEST_ASSERT_EQ_SINT( "Test that the accel flag is/isn't set.", acc_detect_flag, expected[test_num][i] );
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
/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
	{
	{ "launch_detection", test_launch_detection }
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "launch_detect.c", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/