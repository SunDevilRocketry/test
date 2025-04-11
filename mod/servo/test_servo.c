/*******************************************************************************
*
* FILE: 
*      test_servo.c
*
* DESCRIPTION: 
*      Unit tests for functions in the servo.c module.
*
* NOTE: 
*	   This is pasted from a template that includes some functions used
*	   in early GPS testing. Take a look at some other tests to find better
*	   examples.
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
#include "servo.h"

/* unity.h is required for all unit tests. Other headers should be added if they
   are relevant to the test. */

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
// UART_HandleTypeDef huart4;  /* GPS */
SERVO_PRESET servo_preset;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart6;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/
#define EXPECTED_COVERAGE 100 /* set this to 100 to specify full coverage */

/*------------------------------------------------------------------------------
Procedures: Test Helpers // Any misc functions that need to be called by tests
------------------------------------------------------------------------------*/


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
*       test_servo_init		  				                                   *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the initialization of the servo module.						   *
*                                                                              *
*******************************************************************************/
void test_servo_init
	(
	void
    )
{
/* Step: Set up test */
#define NUM_CASES_INIT 3
printf("\nUnit Tests: test_servo_init\n");
MOCK_hal_init();

/* Step: Set up test vectors (inputs, expected) */
typedef struct test_vector {
	HAL_StatusTypeDef hal_status1_in;
	HAL_StatusTypeDef hal_status2_in;
	HAL_StatusTypeDef hal_status3_in;
	HAL_StatusTypeDef hal_status4_in;
	SERVO_STATUS	  status;
} test_vector;

test_vector cases[NUM_CASES_INIT] =
{
	{	HAL_OK, 	HAL_OK, 	HAL_OK, 	HAL_OK, 	SERVO_OK	},
	{	HAL_OK, 	HAL_OK, 	HAL_ERROR, 	HAL_OK, 	SERVO_FAIL	},
	{	HAL_ERROR, 	HAL_ERROR, 	HAL_ERROR, 	HAL_ERROR, 	SERVO_FAIL	}
};

/* Step: Execute tests */
for ( int test_num = 0; test_num < NUM_CASES_INIT; test_num++ )
	{
	MOCK_HAL_TIM_PWM_Start( (4*test_num), cases[test_num].hal_status1_in );
	MOCK_HAL_TIM_PWM_Start( (4*test_num + 1), cases[test_num].hal_status2_in );
	MOCK_HAL_TIM_PWM_Start( (4*test_num + 2), cases[test_num].hal_status3_in );
	MOCK_HAL_TIM_PWM_Start( (4*test_num + 3), cases[test_num].hal_status4_in );
	TEST_ASSERT_EQUAL_INT(cases[test_num].status, servo_init());
	printf("\tservo_init #%d passed\n", test_num + 1); // prints a 1-indexed number instead of 0-indexed
	}

#undef NUM_CASES_INIT

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
UNITY_BEGIN();
printf("-----------------------\n");
printf("	SERVO UNIT TESTING\n");
printf("-----------------------\n");
printf("\nNote: These unit tests exit on a failed assert. If the test fails, go to the case after the last pass.\n");

// List test functions here.
RUN_TEST( test_servo_init );

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