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

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/

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
	/* Call function under test*/

	/* Check result*/
	TEST_ASSERT_EQ_SINT( "Test that the result equals the expected", 1, 1 );
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
// TODO add the struct references
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
TEST_INITIALIZE_TEST( "fin_calib", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/