/*******************************************************************************
*
* FILE: 
*      test_blank.c
*
* DESCRIPTION: 
*      Unit tests for functions in the xxxxxxxxxxxx module.
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

/* unity.h is required for all unit tests. Other headers should be added if they
   are relevant to the test. */

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart4;  /* GPS */

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

/* Step: Set up test vectors (inputs, expected) */
int inputs[NUM_CASES_BAR] = 
{
#include "cases/blank_inputs.txt"
};

int expected[NUM_CASES_BAR] = 
{
#include "cases/blank_expected.txt"
};

/* Step: Execute tests */
for ( int test_num = 0; test_num < NUM_CASES_BAR; test_num++ )
	{
	TEST_ASSERT_EQUAL_INT(expected[test_num], foo(inputs[test_num]));
	printf("\tgps_mesg_validate #%d passed\n", test_num + 1); // prints a 1-indexed number instead of 0-indexed
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
UNITY_BEGIN();
printf("-----------------------\n");
printf("	XXXXXXX UNIT TESTING\n");
printf("-----------------------\n");
printf("\nNote: These unit tests exit on a failed assert. If the test fails, go to the case after the last pass.\n");

// List test functions here.
RUN_TEST( test_bar );

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