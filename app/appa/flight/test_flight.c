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

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Procedures: Test Helpers
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
int foo
	(
	int input
	) 
{
return input + 1;

} /* foo */


/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_bar		  				                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Basic example test													   *
*                                                                              *
*******************************************************************************/
void test_bar 
	(
	void
    )
{
/* Step: Set up test */
#define NUM_CASES_BAR 3
printf("\nUnit Tests: test_bar\n");

/* Step: Execute tests */
for ( int test_num = 0; test_num < NUM_CASES_BAR; test_num++ )
	{
	/* Call function under test*/

	/* Check result*/
	TEST_ASSERT_EQ_UINT( "Test that the result equals the expected", foo(test_num), test_num + 1);
	}

} /* test_bar */


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
	{ "bar", test_bar } /* Callback to function. All you need to do is write a message in a string and the function name! */
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "flight", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/