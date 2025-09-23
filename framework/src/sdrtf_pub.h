/*******************************************************************************
*
* FILE: 
* 		sdrtf_pub.h
*
* DESCRIPTION: 
* 		The Sun Devil Rocketry embedded test framework.
*
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDRTF_PUB_GUARD_H
#define SDRTF_PUB_GUARD_H

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------------
 Includes 
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------
 Macros and Globals 
------------------------------------------------------------------------------*/
/* Tolerances */
#define DFLT_FLOAT_TOLERANCE 0.0001f

/* Initialize Test */
#define TEST_INITIALIZE_TEST( test_suite_name, test_array ) _test_init( test_suite_name, test_array, (sizeof(test_array) / sizeof(test_array[0])) )

/* Asserts */
#define TEST_ASSERT_TRUE( msg, actual ) _test_assert( ASSERT_TYPE_EQ, msg, actual, __LINE__, __FILE__ )
#define TEST_ASSERT_FALSE( msg, actual ) _test_assert( ASSERT_TYPE_NE, msg, actual, __LINE__, __FILE__ )

#define TEST_ASSERT_EQ_FLOAT( msg, actual, expected ) _test_assert_float( ASSERT_TYPE_EQ, msg, actual, expected, DFLT_FLOAT_TOLERANCE, __LINE__, __FILE__ )
#define TEST_ASSERT_NE_FLOAT( msg, actual, expected ) _test_assert_float( ASSERT_TYPE_NE, msg, actual, expected, DFLT_FLOAT_TOLERANCE, __LINE__, __FILE__ )
#define TEST_ASSERT_LT_FLOAT( msg, actual, expected ) _test_assert_float( ASSERT_TYPE_LT, msg, actual, expected, DFLT_FLOAT_TOLERANCE, __LINE__, __FILE__ )
#define TEST_ASSERT_GT_FLOAT( msg, actual, expected ) _test_assert_float( ASSERT_TYPE_GT, msg, actual, expected, DFLT_FLOAT_TOLERANCE, __LINE__, __FILE__ )
#define TEST_ASSERT_LE_FLOAT( msg, actual, expected ) _test_assert_float( ASSERT_TYPE_LE, msg, actual, expected, DFLT_FLOAT_TOLERANCE, __LINE__, __FILE__ )
#define TEST_ASSERT_GE_FLOAT( msg, actual, expected ) _test_assert_float( ASSERT_TYPE_GE, msg, actual, expected, DFLT_FLOAT_TOLERANCE, __LINE__, __FILE__ )

#define TEST_ASSERT_EQ_UINT( msg, actual, expected ) _test_assert_uint( ASSERT_TYPE_EQ, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_NE_UINT( msg, actual, expected ) _test_assert_uint( ASSERT_TYPE_NE, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_LT_UINT( msg, actual, expected ) _test_assert_uint( ASSERT_TYPE_LT, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_GT_UINT( msg, actual, expected ) _test_assert_uint( ASSERT_TYPE_GT, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_LE_UINT( msg, actual, expected ) _test_assert_uint( ASSERT_TYPE_LE, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_GE_UINT( msg, actual, expected ) _test_assert_uint( ASSERT_TYPE_GE, msg, actual, expected, __LINE__, __FILE__ )

#define TEST_ASSERT_EQ_SINT( msg, actual, expected ) _test_assert_sint( ASSERT_TYPE_EQ, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_NE_SINT( msg, actual, expected ) _test_assert_sint( ASSERT_TYPE_NE, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_LT_SINT( msg, actual, expected ) _test_assert_sint( ASSERT_TYPE_LT, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_GT_SINT( msg, actual, expected ) _test_assert_sint( ASSERT_TYPE_GT, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_LE_SINT( msg, actual, expected ) _test_assert_sint( ASSERT_TYPE_LE, msg, actual, expected, __LINE__, __FILE__ )
#define TEST_ASSERT_GE_SINT( msg, actual, expected ) _test_assert_sint( ASSERT_TYPE_GE, msg, actual, expected, __LINE__, __FILE__ )

#define TEST_ASSERT_EQ_MEMORY( msg, actual, expected, size ) _test_assert_memory( ASSERT_TYPE_EQ, msg, actual, expected, size, __LINE__, __FILE__ )
#define TEST_ASSERT_NE_MEMORY( msg, actual, expected, size ) _test_assert_memory( ASSERT_TYPE_NE, msg, actual, expected, size, __LINE__, __FILE__ )

#define TEST_ASSERT_EQ_STRING( msg, actual, expected, size ) _test_assert_string( ASSERT_TYPE_EQ, msg, actual, expected, size, __LINE__, __FILE__ )
#define TEST_ASSERT_NE_STRING( msg, actual, expected, size ) _test_assert_string( ASSERT_TYPE_NE, msg, actual, expected, size, __LINE__, __FILE__ )

/*------------------------------------------------------------------------------
 Typdefs 
------------------------------------------------------------------------------*/
/* Assert type is used inside each assert function. Largely abstracted from
   test writers.    */
typedef enum {
    ASSERT_TYPE_EQ, /* Equal to */
    ASSERT_TYPE_GT, /* Greater than */
    ASSERT_TYPE_LT, /* Less than */
    ASSERT_TYPE_GE, /* Greater than or equal to */
    ASSERT_TYPE_LE, /* Less than or equal to */
    ASSERT_TYPE_NE  /* Not equal */
} ASSERT_TYPE;

/* Pointer to a test function. All tests should have the signature:
   void example_test_name() */
typedef void (*test_callback)(void);

/* A test should have a name and a pointer to the test function. */
typedef struct unit_test {
	const char* test_name;
	test_callback test_pointer;
} unit_test;

/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/

/* test_runner.c */
void TEST_begin_nested_case
    (
    const char* case_description
    );

void TEST_end_nested_case
    (
    void
    );

void _test_init
    ( 
    const char* test_name_in,
    unit_test* test_array,
    uint16_t test_array_count
    );

/* test_assert.c */
void _test_assert
    (
    ASSERT_TYPE assert_type,
    const char* msg,
    bool actual,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    );

void _test_assert_float
    (
    ASSERT_TYPE assert_type,
    const char* msg,
    float actual, 
    float expected,
    float tolerance,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    );

void _test_assert_uint
    (
    ASSERT_TYPE assert_type,
    const char* msg,
    uint32_t actual, 
    uint32_t expected,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    );

void _test_assert_sint
    (
    ASSERT_TYPE assert_type,
    const char* msg,
    int32_t actual, 
    int32_t expected,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    );

void _test_assert_memory
    (
    ASSERT_TYPE assert_type,
    const char* msg,
    void* actual, 
    void* expected,
    size_t size,
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    );

void _test_assert_string
    (
    ASSERT_TYPE assert_type,
    const char* msg,
    char* actual, 
    char* expected,
    size_t size, /* maximum size of the string */
    uint32_t line, /* pass in __LINE__ from the caller */
    const char* file /* pass in __FILE__ from the caller */
    );

#ifdef __cplusplus
}
#endif

#endif /* SDRTF_PUB_GUARD_H */

/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/