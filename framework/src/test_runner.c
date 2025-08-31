/*******************************************************************************
*
* FILE: 
*      test_runner.c
*
* DESCRIPTION: 
*      A driver for unit tests on Sun Devil Rocketry embedded code.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "sdrtf_pub.h"
#include "sdrtf_prv.h"

/*------------------------------------------------------------------------------
Externs
------------------------------------------------------------------------------*/
FILE* outfile_handle = NULL;
char test_name[32];
uint32_t fail_counter;
uint32_t pass_counter;

/*------------------------------------------------------------------------------
Locals
------------------------------------------------------------------------------*/
uint32_t passes_since_last_group;
uint32_t fails_since_last_group;
bool     in_test_group;
bool     in_nested_case;
uint32_t nested_case_num;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Procedure Prototypes
------------------------------------------------------------------------------*/

static void print_test_header
    (
    void
    );

/*------------------------------------------------------------------------------
Procedures
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_begin_nested_case                                                 *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Begin the nested test case.                                            *
*                                                                              *
*******************************************************************************/
void TEST_begin_nested_case
    (
    const char* case_description
    )
{

if( in_test_group && !in_nested_case )
    {
    fprintf( outfile_handle, "-> BEGIN TEST CASE %d: %s\n\n", nested_case_num, case_description );
    in_nested_case = true;
    }
else
    {
    _test_error( "Tried to open test case before closing previous." );
    }

} /* TEST_begin_nested_case */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_end_nested_case                                                   *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		End the test group.                                                    *
*                                                                              *
*******************************************************************************/
void TEST_end_nested_case
    (
    void
    )
{
if( in_test_group )
    {
    fprintf( outfile_handle, "-> END TEST CASE\n\n" );
    in_nested_case = false;
    nested_case_num++;
    }
else
    {
    _test_error( "Tried to close test case while not in one." );
    }

} /* TEST_end_nested_case */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_init                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Initialize a unit test.                                                *
*                                                                              *
*******************************************************************************/
void _test_init
    ( 
    const char* test_name_in,
    unit_test* test_array,
    uint16_t test_array_count
    )
{
FILE* outfile = fopen( "results.txt", "w" );

/*------------------------------------------------------------------------------
Validate Inputs
------------------------------------------------------------------------------*/
if( outfile == NULL || test_name_in == NULL )
    {
    _test_error( "Null pointers given to test_init." );
    }

/*------------------------------------------------------------------------------
Set Globals
------------------------------------------------------------------------------*/
outfile_handle = outfile;
strcpy( test_name, test_name_in );
fail_counter = 0;
pass_counter = 0;
passes_since_last_group = 0;
fails_since_last_group = 0;
in_test_group = false;

/*------------------------------------------------------------------------------
Write Header Output
------------------------------------------------------------------------------*/
print_test_header();

/*------------------------------------------------------------------------------
Run Tests
------------------------------------------------------------------------------*/
for( int i = 0; i < test_array_count; i++ )
	{
	_test_begin_group( test_array[i].test_name );
	test_array[i].test_pointer();
	_test_end_group( test_array[i].test_name );
	}

/*------------------------------------------------------------------------------
Finalize Tests
------------------------------------------------------------------------------*/
_test_finalize();

} /* _test_init */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_begin_group                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Begin the test group.                                                  *
*                                                                              *
*******************************************************************************/
void _test_begin_group
    (
    const char* group_description
    )
{
if( !in_test_group && !in_nested_case )
    {
    fprintf( outfile_handle, "\n--BEGIN TEST GROUP: %s--\n\n", group_description );
    in_test_group = true;
    nested_case_num = 0;
    }
else
    {
    _test_error( "Tried to open test group before closing previous." );
    }

} /* _test_begin_group */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_end_group                                                         *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		End the test group.                                                    *
*                                                                              *
*******************************************************************************/
void _test_end_group
    (
    const char* group_description
    )
{
if( in_test_group )
    {
    fprintf( outfile_handle, "--TEST GROUP RESULTS:--\n" );
    fprintf( outfile_handle, "Group Passes: %d\n", pass_counter - passes_since_last_group );
    fprintf( outfile_handle, "Group Fails:  %d\n", fail_counter - fails_since_last_group );
    fprintf( outfile_handle, "--END TEST GROUP: %s--\n\n", group_description );
    passes_since_last_group = pass_counter;
    fails_since_last_group = fail_counter;
    in_test_group = false;
    in_nested_case = false;
    }
else
    {
    _test_error( "Tried to close test group while not in one." );
    }
} /* _test_end_group */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_finalize                                                         *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Finalize the test.                                                     *
*                                                                              *
*******************************************************************************/
void _test_finalize
    (
    void
    )
{
char status[5];
if( fail_counter == 0 )
    {
    strcpy( status, "PASS" );
    }
else
    {
    strcpy( status, "FAIL" ); /* if even one case fails, the whole test fails */
    }

/* formatted footer */
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "-------------Test Complete--------------\n" );
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "Passes: %d\n", pass_counter );
fprintf( outfile_handle, "Fails:  %d\n", fail_counter );
fprintf( outfile_handle, "Result: %s\n", status );
fprintf( outfile_handle, "----------------------------------------\n" );

/* will be zero with no fails. Else, returns a negative error code indicating num fails */
exit( -1 * fail_counter );

} /* _test_finalize */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_error                                                             *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Abort the test immediately and report the error.                       *
*                                                                              *
*******************************************************************************/
void _test_error
    (
    const char* msg
    )
{
/* log to console */
printf( "Test aborted with error: %s", msg );

/* log to file if applicable */
if( outfile_handle != NULL )
    {
    fprintf( outfile_handle, "\nTest aborted with error: %s\n", msg );
    }

/* abort */
exit(1);

}


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_fail                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Fail a comparison and log the result.                                  *
*                                                                              *
*******************************************************************************/
void _test_fail
    (
    const char* msg,
    const char* err_msg
    )
{
/* log fails both to the results file and to console */
fprintf( outfile_handle, "%s\n", msg );
fprintf( outfile_handle, "FAIL: %s\n", err_msg );
printf( "%s\n", msg );
printf( "FAIL: %s\n\n", err_msg );
fail_counter++;
} /* _test_fail */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		_test_pass                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Pass a comparison and log the result.                                  *
*                                                                              *
*******************************************************************************/
void _test_pass
    (
    const char* msg
    )
{
/* log result, increment counter */
fprintf( outfile_handle, "%s\n", msg );
pass_counter++;
} /* _test_pass */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		print_test_header                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Helper function to print test environment information.                 *
*                                                                              *
*******************************************************************************/
static void print_test_header
    (
    void
    )
{
/* Get locals */
time_t curr_time = time( NULL );
struct tm tm = *localtime( &curr_time );
char date[20];
char time[20];
bool repo_clean = true;

/* Format strings to match C macros*/
strftime( date, sizeof(date), "%b %d %Y", &tm );
strftime( time, sizeof(time), "%H:%M:%S", &tm );

/* Print top header */
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "-----------Sun Devil Rocketry-----------\n" );
fprintf( outfile_handle, "-----------Unit Test Results------------\n" );
fprintf( outfile_handle, "----------------------------------------\n\n" );

/* Test Environment Information */
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "------------Test Environment------------\n" );
fprintf( outfile_handle, "----------------------------------------\n\n" );
fprintf( outfile_handle, "--General Build Information--\n" );
fprintf( outfile_handle, "Test Name:   %s\n", test_name );
fprintf( outfile_handle, "Build Date:  %s\n", __DATE__ );
fprintf( outfile_handle, "Build Time:  %s\n", __TIME__ );
fprintf( outfile_handle, "Run Date:    %s\n", date );
fprintf( outfile_handle, "Run Time:    %s\n", time );

/* Is using ISO C compiler? */
#if( defined( __STDC__ ) && __STDC__ )
fprintf( outfile_handle, "ISO C?:      %d\n", __STDC__ );
fprintf( outfile_handle, "C Standard:  %ld\n", __STDC_VERSION__ );
#else
fprintf( outfile_handle, "ISO C?:      %d\n", 0 );
#endif

/* GNU compilers*/
#if( defined( __GNUC__ ) && __GNUC__ )
fprintf( outfile_handle, "\n--GNU C Compiler (GCC) Info--\n" );
fprintf( outfile_handle, "GCC Version: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ );
#endif


/* Run test environment checks */
fprintf( outfile_handle, "\n----------------------------------------\n" );
fprintf( outfile_handle, "----------------Results-----------------\n" );
fprintf( outfile_handle, "----------------------------------------\n\n" );

_test_begin_group( "Check test environment" );

/* Requires an ISO C compiler. We use features up to C17. */
#if( defined( __STDC__ ) && __STDC__ )
TEST_ASSERT_GE_UINT( "Test Environment: ISO C standard is C17 or greater", __STDC_VERSION__, 201700L );
#else
TEST_ASSERT_TRUE( "Test Environment: ISO C standard not defined", false );
#endif

/* Only GCC 12+ is supported at the moment. Future update could expand to clang if desired. */
#if( defined( __GNUC__ ) && __GNUC__ )
TEST_ASSERT_GE_UINT( "Test Environment: Compiler is supported GCC version", __GNUC__, TEST_MIN_SUPPORTED_GCC_VERSION );
#else
TEST_ASSERT_TRUE( "Test Environment: Unsupported Compiler", false );
#endif

_test_end_group( "Check test environment" );

}
