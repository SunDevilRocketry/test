/*******************************************************************************
*
* FILE: 
*      test_lora.c
*
* DESCRIPTION: 
*      Unit tests for functions in the lora module.
*
* NOTE: 
*	   This is a work-in-progress
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
#include "lora.h"

/* unity.h is required for all unit tests. Other headers should be added if they
   are relevant to the test. */

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
SPI_HandleTypeDef  hspi4;	/* LoRa SPI */

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
*       test_lora_init		  				                                   *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test LoRa modem initiation.											   *
*                                                                              *
*******************************************************************************/

void test_lora_init
	(
	void
	)
{
// TODO: Write function body

// Create LoRa config structure
// Run LoRa init with that struct
// Get values from the SPI reads
// Make the test assertions
}

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