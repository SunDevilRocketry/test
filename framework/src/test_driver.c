/*******************************************************************************
*
* FILE: 
*      test_driver.c
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
* 		TEST_init                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Initialize a unit test.                                                *
*                                                                              *
*******************************************************************************/
void TEST_init
    ( 
    FILE* outfile_handle_in,
    const char* test_name_in
    )
{
/*------------------------------------------------------------------------------
Validate Inputs
------------------------------------------------------------------------------*/
if( outfile_handle_in == NULL || test_name_in == NULL )
    {
    test_error( "Null pointers given to test_init." );
    }

/*------------------------------------------------------------------------------
Set Globals
------------------------------------------------------------------------------*/
outfile_handle = outfile_handle_in;
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

}


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_begin_group                                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Begin the test group.                                                  *
*                                                                              *
*******************************************************************************/
void TEST_begin_group
    (
    const char* group_description
    )
{
if( !in_test_group )
    {
    fprintf( outfile_handle, "\n--BEGIN TEST GROUP: %s--\n\n", group_description );
    in_test_group = true;
    }
else
    {
    test_error( "Tried to open test group before closing previous." );
    }
}


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_end_group                                                         *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		End the test group.                                                    *
*                                                                              *
*******************************************************************************/
void TEST_end_group
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
    }
else
    {
    test_error( "Tried to close test group while not in one." );
    }
}


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_finalize                                                          *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Finalize the test.                                                     *
*                                                                              *
*******************************************************************************/
uint32_t TEST_finalize
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
    strcpy( status, "FAIL" );
    }

fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "-------------Test Complete--------------\n" );
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "Passes: %d\n", pass_counter );
fprintf( outfile_handle, "Fails:  %d\n", fail_counter );
fprintf( outfile_handle, "Result: %s\n", status );
fprintf( outfile_handle, "----------------------------------------\n" );

return fail_counter;
}


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		test_error                                                             *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Abort the test immediately and report the error.                       *
*                                                                              *
*******************************************************************************/
void test_error
    (
    char* msg
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
* 		test_fail                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Fail a comparison and log the result.                                  *
*                                                                              *
*******************************************************************************/
void test_fail
    (
    char* msg,
    char* err_msg
    )
{
fprintf( outfile_handle, "%s\n", msg );
fprintf( outfile_handle, "FAIL: %s\n", err_msg );
printf( "%s\n", msg );
printf( "FAIL: %s\n\n", err_msg );
fail_counter++;
}


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		test_pass                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Pass a comparison and log the result.                                  *
*                                                                              *
*******************************************************************************/
void test_pass
    (
    char* msg
    )
{
fprintf( outfile_handle, "%s\n", msg );
pass_counter++;
}


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

strftime( date, sizeof(date), "%b %d %Y", &tm );
strftime( time, sizeof(time), "%H:%M:%S", &tm );

/* Print top header */
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "-----------Sun Devil Rocketry-----------\n" );
fprintf( outfile_handle, "-----------Unit Test Results------------\n" );
fprintf( outfile_handle, "----------------------------------------\n\n" );

/* Test Environment */
fprintf( outfile_handle, "----------------------------------------\n" );
fprintf( outfile_handle, "------------Test Environment------------\n" );
fprintf( outfile_handle, "----------------------------------------\n\n" );
fprintf( outfile_handle, "--General Build Information--\n" );
fprintf( outfile_handle, "Test Name:   %s\n", test_name );
fprintf( outfile_handle, "Build Date:  %s\n", __DATE__ );
fprintf( outfile_handle, "Build Time:  %s\n", __TIME__ );
fprintf( outfile_handle, "Run Date:    %s\n", date );
fprintf( outfile_handle, "Run Time:    %s\n", time );
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

fprintf( outfile_handle, "\n--Formal Test Run Info--\n" );
#if( defined( TEST_FORMAL_RUN ) && TEST_FORMAL_RUN )
fprintf( outfile_handle, "Run Type:    FORMAL\n" );
#else
fprintf( outfile_handle, "Run Type:    INFORMAL\n\n" );
#endif

/* Run test environment checks */
fprintf( outfile_handle, "\n----------------------------------------\n" );
fprintf( outfile_handle, "----------------Results-----------------\n" );
fprintf( outfile_handle, "----------------------------------------\n\n" );

#if( defined( __STDC__ ) && __STDC__ )
TEST_ASSERT_GE_UINT( "Test Environment: ISO C standard is C17 or greater", __STDC_VERSION__, 201700L );
#else
TEST_ASSERT_TRUE( "Test Environment: ISO C standard not defined", false );
#endif

#if( defined( __GNUC__ ) && __GNUC__ )
TEST_ASSERT_GE_UINT( "Test Environment: Compiler is supported GCC version", __GNUC__, TEST_MIN_SUPPORTED_GCC_VERSION );
#else
TEST_ASSERT_TRUE( "Test Environment: Unsupported Compiler", false );
#endif

#if( defined( TEST_FORMAL_RUN ) && TEST_FORMAL_RUN )
TEST_ASSERT_TRUE( "Test Environment: Repository is clean.", repo_clean );
#endif


}
