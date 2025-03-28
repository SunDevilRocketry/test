/*******************************************************************************
*
* FILE: 
*      test_gps.c
*
* DESCRIPTION: 
*      Unit tests for functions in the gps module.
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
#include "main.h"
#include "sensor.h"
#include "gps.h"
#include "unity.h"


/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart4;  /* GPS */


/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/
#define EXPECTED_COVERAGE 100

/*------------------------------------------------------------------------------
Procedures: Test Helpers
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       printChar                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Helper function for gpsStructToCSV. Prints '0' instead of null.		   *
*		Used for test_GPS_parse.										       *
*                                                                              *
*******************************************************************************/
void printChar(FILE* f, char c) {
	if (c == 0) {
		fprintf(f, "0,");
	}
	else {
		fprintf(f, "%c,", c);
	}
} /* printChar */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       gpsStructToCSV                                                         *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Helper function for test_GPS_parse. Outputs GPS_DATA struct to csv.    *
*                                                                              *
*******************************************************************************/
void gpsStructToCSV(GPS_DATA* data, FILE* f) {
	// calculated values
	fprintf(f, "%f,", data->dec_latitude);
    fprintf(f, "%f,", data->dec_longitude);
	fprintf(f, "%f,", data->altitude_ft);

    // GGA - Global Positioning System Fixed Data
	fprintf(f, "%f,", data->nmea_longitude);
	fprintf(f, "%f,", data->nmea_latitude);
	fprintf(f, "%f,", data->utc_time);
	printChar(f, data->ns);
	printChar(f, data->ew);
	fprintf(f, "%d,", data->lock);
	fprintf(f, "%d,", data->satelites);
	fprintf(f, "%f,", data->hdop);
	fprintf(f, "%f,", data->msl_altitude);
	printChar(f, data->msl_units);

    // RMC - Recommended Minimmum Specific GNS Data
	printChar(f, data->rmc_status);
	fprintf(f, "%f,", data->speed_k);
	fprintf(f, "%f,", data->course_d);
	fprintf(f, "%d,", data->date);

    // GLL
	printChar(f, data->gll_status);

    // VTG - Course over ground, ground speed
	fprintf(f, "%f,", data->course_t);
	printChar(f, data->course_t_unit);
	fprintf(f, "%f,", data->course_m);
	printChar(f, data->course_m_unit);
	printChar(f, data->speed_k_unit);
    fprintf(f, "%f,", data->speed_km);
	if (data->speed_km_unit == 0) {
		fprintf(f, "0");
	}
	else {
		fprintf(f, "%c", data->speed_km_unit);
	}
	fprintf(f, "\n");
} /* gpsStructToCSV */


/*------------------------------------------------------------------------------
Procedures: Unity Functions
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
Procedures: Tests
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_GPS_parse			                                               *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the parser for NMEA strings. 									   *
*                                                                              *
*******************************************************************************/
void test_GPS_parse 
	(
	void
    )
{
/*------------------------------------------------------------------------------
Initializations
------------------------------------------------------------------------------*/
int num_cases = 15;
char buffer[200] = ""; // An NMEA message is 82 characters, but the way we parse may end up with more in order to represent the struct

// Source: https://github.com/esutton/gps-nmea-log-files/blob/master/AMOD_AGL3080_20121104_134730.txt

printf("\nUnit Tests: GPS_parse (and static helper functions)\n");

/* Step: Load inputs and expected results */
char* input_strings[] = 
{
#include "cases/NMEA_inputs.txt"
};

char* expected[] =
{
#include "cases/gps_parse_expected.txt"
};

/* Step: Parse inputs and output actual results to file */
GPS_DATA data;
FILE* f = fopen("cases/gps_parse_actual.txt", "w");
for ( int i = 0; i < num_cases; i++ ) 
	{
	memset(&data, 0, sizeof(data));
	GPS_parse(&data, input_strings[i]);
	gpsStructToCSV(&data, f);
	}
fclose(f);

/* Step: Compare actual and expected */

FILE* actual = fopen("cases/gps_parse_actual.txt", "r");
for ( int test_num = 0; test_num < num_cases; test_num++ )
	{
	fgets(buffer, sizeof(buffer), actual);
    /* Initialize input/output */
	buffer[strcspn(buffer, "\n")] = 0;
	TEST_ASSERT_EQUAL_STRING(expected[test_num], buffer); /* Test begins */
	printf("\tGPS_Parse #%d passed\n", test_num + 1);
	}

} /* test_GPS_parse */

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_gps_mesg_validate			                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the validation function for NMEA sentences						   *
*                                                                              *
*******************************************************************************/
void test_gps_mesg_validate 
	(
	void
    )
{
/*------------------------------------------------------------------------------
Initializations
------------------------------------------------------------------------------*/
#define NUM_CASES_GPS_MESG_VALIDATE 5
char buffer[200] = ""; // An NMEA message is 82 characters, but the way we parse may end up with more in order to represent the struct

// Source: https://github.com/esutton/gps-nmea-log-files/blob/master/AMOD_AGL3080_20121104_134730.txt

printf("\nUnit Tests: test_gps_mesg_validate\n");

/* Step: Load inputs and expected results */
char* input_strings[] = 
{
#include "cases/gps_mesg_validate_inputs.txt"
};

int expected[NUM_CASES_GPS_MESG_VALIDATE] = {1,1,1,0,0};

for ( int test_num = 0; test_num < NUM_CASES_GPS_MESG_VALIDATE; test_num++ )
	{
	TEST_ASSERT_EQUAL_INT(expected[test_num], gps_mesg_validate(input_strings[test_num]));
	printf("\tgps_mesg_validate #%d passed\n", test_num + 1);
	}

} /* test_GPS_mesg_validate */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_gps_transmit				                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the transmission function for gps.								   *
*		COVERAGE ISSUE - This function is currently never called.			   *
*       Instead, we will merely be testing error handling.                     *
*                                                                              *
*******************************************************************************/
void test_gps_transmit
	(
	void
    )
{
/*------------------------------------------------------------------------------
Initializations
------------------------------------------------------------------------------*/
#define NUM_CASES_GPS_TRANSMIT 4

printf("\nUnit Tests: test_gps_transmit\n");
printf("(NOTE: This tests exists for statement coverage in gps.c only. It does not verify lower functionalities.)\n");

/* Step: Prepare mocked function returns */
HAL_StatusTypeDef statuses[NUM_CASES_GPS_TRANSMIT] =
{
HAL_OK,
HAL_ERROR,
HAL_BUSY,
HAL_TIMEOUT
}; // These happen to be the same as the expected returns

// Set function inputs
size_t size = 8;
void* tx_data_ptr = malloc(size);
uint16_t timeout = 10000;

for ( int test_num = 0; test_num < NUM_CASES_GPS_TRANSMIT; test_num++ )
	{
	MOCK_HAL_Status_Return(statuses[test_num]);
	TEST_ASSERT_EQUAL_INT(statuses[test_num], gps_transmit(tx_data_ptr, size, timeout));
	printf("\tgps_transmit #%d passed\n", test_num + 1);
	}
free(tx_data_ptr);
} /* test_gps_transmit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_gps_receive				                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the reception function for gps.								   *
*		COVERAGE ISSUE - This function is currently never called.			   *
*       Instead, we will merely be testing error handling.                     *
*                                                                              *
*******************************************************************************/
void test_gps_receive
	(
	void
    )
{
/*------------------------------------------------------------------------------
Initializations
------------------------------------------------------------------------------*/
#define NUM_CASES_GPS_RECEIVE 4

printf("\nUnit Tests: test_gps_receive\n");
printf("(NOTE: This tests exists for statement coverage in gps.c only. It does not verify lower functionalities.)\n");

/* Step: Prepare mocked function returns */
HAL_StatusTypeDef statuses[NUM_CASES_GPS_RECEIVE] =
{
HAL_OK,
HAL_ERROR,
HAL_BUSY,
HAL_TIMEOUT
}; // These happen to be the same as the expected returns

/* Step: Prepare expected */
HAL_StatusTypeDef expected[NUM_CASES_GPS_RECEIVE] =
{
HAL_OK,
GPS_FAIL,
GPS_FAIL,
GPS_TIMEOUT
}; // These happen to be the same as the expected returns

// Set function inputs
size_t size = 8;
void* tx_data_ptr = malloc(size);
uint16_t timeout = 10000;

for ( int test_num = 0; test_num < NUM_CASES_GPS_RECEIVE; test_num++ )
	{
	MOCK_HAL_Status_Return(statuses[test_num]);
	TEST_ASSERT_EQUAL_INT(expected[test_num], gps_receive(tx_data_ptr, size, timeout));
	printf("\tgps_receive #%d passed\n", test_num + 1);
	}
free(tx_data_ptr);
} /* test_gps_receive */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       test_gps_receive_IT				                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Test the interrupt handler gps reception function.					   *
*		COVERAGE ISSUE - This function is currently never called.			   *
*       Instead, we will merely be testing error handling.                     *
*                                                                              *
*******************************************************************************/
void test_gps_receive_IT
	(
	void
    )
{
/*------------------------------------------------------------------------------
Initializations
------------------------------------------------------------------------------*/
#define NUM_CASES_GPS_RECEIVE_IT 4

printf("\nUnit Tests: test_gps_receive_IT\n");
printf("(NOTE: This tests exists for statement coverage in gps.c only. It does not verify lower functionalities.)\n");

/* Step: Prepare mocked function returns */
HAL_StatusTypeDef statuses[NUM_CASES_GPS_RECEIVE_IT] =
{
HAL_OK,
HAL_ERROR,
HAL_BUSY,
HAL_TIMEOUT
}; // These happen to be the same as the expected returns

/* Step: Prepare expected */
HAL_StatusTypeDef expected[NUM_CASES_GPS_RECEIVE_IT] =
{
HAL_OK,
GPS_FAIL,
GPS_FAIL,
GPS_TIMEOUT
}; // These happen to be the same as the expected returns

// Set function inputs
size_t size = 8;
void* tx_data_ptr = malloc(size);

for ( int test_num = 0; test_num < NUM_CASES_GPS_RECEIVE_IT; test_num++ )
	{
	MOCK_HAL_Status_Return(statuses[test_num]);
	TEST_ASSERT_EQUAL_INT(expected[test_num], gps_receive_IT(tx_data_ptr, size));
	printf("\tgps_receive_IT #%d passed\n", test_num + 1);
	}

free(tx_data_ptr);
} /* test_gps_receive_IT */


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
printf("	GPS UNIT TESTING\n");
printf("-----------------------\n");
printf("\nNote: These unit tests exit on a failed assert. If the test fails, go to the case after the last pass.\n");

// List test functions here.
RUN_TEST( test_GPS_parse );
RUN_TEST( test_gps_mesg_validate );
RUN_TEST( test_gps_transmit );
RUN_TEST( test_gps_receive );
RUN_TEST( test_gps_receive_IT );

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