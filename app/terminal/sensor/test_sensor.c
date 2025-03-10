/*******************************************************************************
*
* FILE: 
*       test_sensor.c
*
* DESCRIPTION: 
*      Unit tests for functions in the sensor module 
*
*******************************************************************************/

/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdint.h>
#include <string.h>


/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "unity.h"
#include "main.h"

/* CMSIS/HAL */
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_conf.h"

/* File under test */
// #include "sensor.c"


/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/
#define NUM_TESTS_readings_to_bytes ( 2 )


/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart1; /* USB UART handler struct        */


/*------------------------------------------------------------------------------
Function Prototypes
------------------------------------------------------------------------------*/

/* Code to run prior to any test */
void setUp
	(
	void
	);

/* Code to run after tests */
void tearDown 
	(
	void
	);

/* tests the reading_to_bytes function in sensor.c */
void test_readings_to_bytes 
	(
	void
	);


/*------------------------------------------------------------------------------
Types
------------------------------------------------------------------------------*/

/* readings_to_bytes test data type */
typedef struct 
	{
	uint32_t Src_buffer[   NUM_SENSORS ];
	uint8_t  Dst_buffer[ 4*NUM_SENSORS ];
    } readings_to_bytes__test_type;


/*------------------------------------------------------------------------------
Procedures 
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


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_readings_to_bytes                                                 *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       tests the reading_to_bytes function in sensor.c                        *
*                                                                              *
*******************************************************************************/
void test_readings_to_bytes 
	(
	void
    )
{
/*------------------------------------------------------------------------------
Local Variables
------------------------------------------------------------------------------*/
uint8_t                      Dst_buffer[ 4*NUM_SENSORS               ];
uint32_t                     Src_buffer[   NUM_SENSORS               ];
uint8_t                      return_val[ 4*NUM_SENSORS               ];

/*------------------------------------------------------------------------------
Initializations
------------------------------------------------------------------------------*/
readings_to_bytes__test_type test_data[] = 
{ 
#include "test_cases/readings_to_bytes.txt"
};

/*------------------------------------------------------------------------------
Run Tests
------------------------------------------------------------------------------*/
for ( int test_num = 0; test_num < NUM_TESTS_readings_to_bytes; ++test_num )
	{
    /* Initialize input/output */	
	memcpy( &Src_buffer[0], &( test_data[test_num].Src_buffer[0] ), sizeof( Src_buffer ) );
	memcpy( &Dst_buffer[0], &( test_data[test_num].Dst_buffer[0] ), sizeof( Dst_buffer ) );
	memset( &return_val[0], 0                                     , sizeof( return_val ) );

	/* Call the fut */
	readings_to_bytes( &return_val[0], &Src_buffer[0] );

	/* Verify correct output */
	TEST_ASSERT_EQUAL_UINT8_ARRAY( Dst_buffer, return_val, 4*NUM_SENSORS );
    }

} /* test_readings_to_bytes */


/*------------------------------------------------------------------------------
Run Tests
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{
UNITY_BEGIN();
RUN_TEST( test_readings_to_bytes );
return UNITY_END();
} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/
