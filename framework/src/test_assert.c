/*******************************************************************************
*
* FILE: 
*      test_assert.c
*
* DESCRIPTION: 
*      Asserts (verify statements) for SDR unit tests.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "sdrtf_pub.h"
#include "sdrtf_prv.h"

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
extern FILE* outfile_handle;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Procedures
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_assert                                                            *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Verify statement on a boolean or logical predicate.                    *
*                                                                              *
*******************************************************************************/
void TEST_assert
    (
    ASSERT_TYPE assert_type,
    char* msg,
    bool actual,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    )
{
/*------------------------------------------------------------------------------
Comparison
------------------------------------------------------------------------------*/
switch( assert_type ) 
    {
    case ASSERT_TYPE_EQ:
        if( actual )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: TRUE | Expected: TRUE\n\n" );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "False at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: FALSE | Expected: TRUE\n\n" );
            return;
            }

    case ASSERT_TYPE_NE:
        if( !actual )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: FALSE | Expected: FALSE\n\n" );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "TRUE at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: TRUE | Expected: FALSE\n\n" );
            return;
            }

    default:
        test_error( "Improper ASSERT_TYPE used for TEST_assert." );
        return;
    }

} /* TEST_assert */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_assert_float                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Verify statement on a float.                                           *
*                                                                              *
*******************************************************************************/
void TEST_assert_float
    (
    ASSERT_TYPE assert_type,
    char* msg,
    float actual, 
    float expected,
    float tolerance,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    )
{
/*------------------------------------------------------------------------------
Comparison
------------------------------------------------------------------------------*/
switch( assert_type ) 
    {
    case ASSERT_TYPE_EQ:
        if( ( expected + tolerance >= actual ) 
         && ( expected - tolerance <= actual ) )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Unequal float at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_NE:
        if( ( expected + tolerance <= actual ) 
         && ( expected - tolerance >= actual ) )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Equal float at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_GT:
        if( actual > expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Less than or equal to float at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_LT:
        if( actual < expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Greater than or equal to float at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_GE:
        if( actual >= expected - tolerance )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Less than float at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_LE:
        if( actual <= expected + tolerance )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Greater than float at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %f | Expected: %f\n\n", actual, expected );
            return;
            }

    default:
        test_error( "Improper ASSERT_TYPE used for TEST_assert_float." );
        return;
    }

} /* TEST_assert_float */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_assert_uint                                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Verify statement on a uint.                                            *
*                                                                              *
*******************************************************************************/
void TEST_assert_uint
    (
    ASSERT_TYPE assert_type,
    char* msg,
    uint32_t actual, 
    uint32_t expected,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    )
{
/*------------------------------------------------------------------------------
Comparison
------------------------------------------------------------------------------*/
switch( assert_type ) 
    {
    case ASSERT_TYPE_EQ:
        if( actual == expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Unequal uint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_NE:
        if( actual != expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Equal uint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_GT:
        if( actual > expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Less than or equal to uint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_LT:
        if( actual < expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Greater than or equal to uint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_GE:
        if( actual >= expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Less than uint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_LE:
        if( actual <= expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Greater than uint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    default:
        test_error( "Improper ASSERT_TYPE used for TEST_assert_uint." );
        return;
    }

} /* TEST_assert_uint */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_assert_sint                                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Verify statement on a sint.                                            *
*                                                                              *
*******************************************************************************/
void TEST_assert_sint
    (
    ASSERT_TYPE assert_type,
    char* msg,
    int32_t actual, 
    int32_t expected,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    )
{
/*------------------------------------------------------------------------------
Comparison
------------------------------------------------------------------------------*/
switch( assert_type ) 
    {
    case ASSERT_TYPE_EQ:
        if( actual == expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Unequal sint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_NE:
        if( actual != expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Equal sint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_GT:
        if( actual > expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Less than or equal to sint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_LT:
        if( actual < expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Greater than or equal to sint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_GE:
        if( actual >= expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Less than sint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    case ASSERT_TYPE_LE:
        if( actual <= expected )
            {
            test_pass( msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }
        else
            {
            char err_msg[128];
            sprintf( err_msg, "Greater than sint at %s:%d", file, line );
            test_fail( msg, err_msg );
            fprintf( outfile_handle, "Actual: %d | Expected: %d\n\n", actual, expected );
            return;
            }

    default:
        test_error( "Improper ASSERT_TYPE used for TEST_assert_sint." );
        return;
    }

} /* TEST_assert_sint */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_assert_memory                                                     *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Verify statement on a region of memory.                                *
*                                                                              *
*******************************************************************************/
void TEST_assert_memory
    (
    ASSERT_TYPE assert_type,
    char* msg,
    void* actual, 
    void* expected,
    size_t size,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    )
{
/*------------------------------------------------------------------------------
Perform Validation
------------------------------------------------------------------------------*/
if( actual == NULL || expected == NULL)
    {
    test_error( "NULLPTR passed to TEST_assert_memory." );
    }

/*------------------------------------------------------------------------------
Byte-by-byte comparison
------------------------------------------------------------------------------*/
switch( assert_type ) 
    {
    case ASSERT_TYPE_EQ:
        for( int i = 0; i < size; i++ )
            {
            if( ((uint8_t*)actual)[i] != ((uint8_t*)expected)[i] )
                {
                char err_msg[128];
                sprintf( err_msg, "Unequal memory at %s:%d", file, line );
                test_fail( msg, err_msg );
                fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
                return; 
                }
            }
        test_pass( msg );
        fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
        return;

    case ASSERT_TYPE_NE:
        for( int i = 0; i < size; i++ )
            {
            if( ((uint8_t*)actual)[i] != ((uint8_t*)expected)[i] )
                {
                test_pass( msg );
                fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
                return;
                }
            }

        char err_msg[128];
        sprintf( err_msg, "Equal memory at %s:%d", file, line );
        test_fail( msg, err_msg );
        fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
        return;

    default:
        test_error( "Improper ASSERT_TYPE used for TEST_assert_memory." );
        return;
    }

} /* TEST_assert_memory */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		TEST_assert_string                                                     *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Verify statement on a C-style string.                                  *
*                                                                              *
*******************************************************************************/
void TEST_assert_string
    (
    ASSERT_TYPE assert_type,
    char* msg,
    char* actual, 
    char* expected,
    size_t size, /* maximum size of the string */
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    )
{
/*------------------------------------------------------------------------------
Perform Validation
------------------------------------------------------------------------------*/
if( actual == NULL || expected == NULL)
    {
    test_error( "NULLPTR passed to TEST_assert_string." );
    }

/*------------------------------------------------------------------------------
Byte-by-byte comparison
------------------------------------------------------------------------------*/
switch( assert_type ) 
    {
    case ASSERT_TYPE_EQ:
        for( int i = 0; i < size; i++ )
            {
            if( ((uint8_t*)actual)[i] != ((uint8_t*)expected)[i] )
                {
                char err_msg[128];
                sprintf( err_msg, "Unequal string at %s:%d", file, line );
                test_fail( msg, err_msg );
                fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
                return; 
                }

            if( ( ((uint8_t*)actual)[i] == ((uint8_t*)expected)[i] ) /* both chars equal */
             && ( ((char*)actual)[i] == '\0' || ((char*)expected)[i] == '\0' ) ) /* null terminator */
                {
                test_pass( msg );
                fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
                return;
                }
            }
        test_pass( msg );
        fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
        return;

    case ASSERT_TYPE_NE:
        for( int i = 0; i < size; i++ )
            {
            if( ((uint8_t*)actual)[i] != ((uint8_t*)expected)[i] )
                {
                test_pass( msg );
                fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x0x%08x\n\n", (int)actual, (int)expected );
                return;
                }

            if( ( ((uint8_t*)actual)[i] == ((uint8_t*)expected)[i] ) /* both chars equal */
             && ( ((char*)actual)[i] == '\0' ) ) /* null terminator */
                {
                char err_msg[128];
                sprintf( err_msg, "Equal string at %s:%d", file, line );
                test_fail( msg, err_msg );
                fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
                return;
                }
            }

        char err_msg[128];
        sprintf( err_msg, "Equal memory at %s:%d", file, line );
        test_fail( msg, err_msg );
        fprintf( outfile_handle, "Actual (address): 0x%08x | Expected (address): 0x%08x\n\n", (int)actual, (int)expected );
        return;

    default:
        test_error( "Improper ASSERT_TYPE used for TEST_assert_string." );
        return;
    }

} /* TEST_assert_string */
