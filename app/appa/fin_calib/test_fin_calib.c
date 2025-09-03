/*******************************************************************************
*
* FILE: 
*      test_fin_calib.c
*
* DESCRIPTION: 
*      Unit tests for functions in the fin_calib module.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "sdrtf_pub.h"
#include "main.h"
#include "test.h"
#include "servo.h"

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/

PRESET_DATA preset_data;

uint8_t usb_test_vals[] = { EXIT };

uint8_t* usb_queue = usb_test_vals;
uint8_t  usb_pos   = 0;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Procedures: Test Helpers
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       _preset_to_array        		  			                           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Convert preset servo values to convenient array for testing			   *
*                                                                              *
*******************************************************************************/
uint8_t* _preset_to_array( PRESET_DATA in_preset ) {
	static uint8_t values[4];

	values[0] = in_preset.servo_preset.rp_servo1;
	values[1] = in_preset.servo_preset.rp_servo2;
	values[2] = in_preset.servo_preset.rp_servo3;
	values[3] = in_preset.servo_preset.rp_servo4;

	return values;
}


/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_usb		  				                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test any codepaths triggered by a USB command.              		   *
*                                                                              *
*******************************************************************************/
void test_usb
	(
	void
    )
{
/* Step: Set up test */
#define NUM_CASES_USB 8
printf("\nUnit Tests: test_usb\n");

/* Step: Set up test vectors (inputs, expected) */
uint8_t inputs[NUM_CASES_USB][2] = 
{
#include "cases/usb_input_queue.txt"
};

uint8_t expected[NUM_CASES_USB][4] = 
{
#include "cases/usb_expected.txt"
};

/* Step: Execute tests */
for ( int test_num = 0; test_num < NUM_CASES_USB; test_num++ )
	{
	usb_queue = inputs[ test_num ];
	usb_pos = 0;

	uint8_t signalIn;

	finCalibration( &signalIn );

	/* Check result*/
	uint8_t* result = _preset_to_array( preset_data );

	/* TODO make this more readable */
	for( int i = 0; i < 4; i++ ) {
		TEST_ASSERT_EQ_SINT( "Test that servo preset equals expected", expected[test_num][i], result[i] );
	}
	//TEST_ASSERT_EQ_SINT( "Test that the result equals the expected", expected[ test_num ] , ( uint8_t[] )  );
	}
} /* test_usb */


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
/*
List of things to fix or fake:
[x] preset_data
[x] led_set_color
[x] motor_drive
[~] usb_receive
*/

/*------------------------------------------------------------------------------
Set up global variables
------------------------------------------------------------------------------*/
SERVO_PRESET servo_preset;
servo_preset.rp_servo1 = 0;
servo_preset.rp_servo2 = 0;
servo_preset.rp_servo3 = 0;
servo_preset.rp_servo4 = 0;

preset_data.servo_preset = servo_preset;

/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
	{
	{ "bar", test_usb } /* Callback to function. All you need to do is write a message in a string and the function name! */
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "fin_calib", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/