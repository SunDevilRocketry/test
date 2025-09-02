/*******************************************************************************
*
* FILE: 
* 		sdrtf_prv.h
*
* DESCRIPTION: 
* 		The Sun Devil Rocketry embedded test framework. Do not include this header
*       in your tests.
*
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDRTF_PRV_GUARD_H
#define SDRTF_PRV_GUARD_H

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
#define TEST_MIN_SUPPORTED_GCC_VERSION 8

/*------------------------------------------------------------------------------
 Typdefs 
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Global Variables 
------------------------------------------------------------------------------*/
extern FILE* outfile_handle;
extern char test_name[32];

/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/

/* test_runner.c */
void _test_begin_group
    (
    const char* group_description
    );

void _test_end_group
    (
    const char* group_description
    );

void _test_finalize
    (
    void
    );
    
void _test_error
    (
    const char* msg
    );

void _test_fail
    (
    const char* msg,
    const char* err_msg
    );

void _test_pass
    (
    const char* msg
    );

#ifdef __cplusplus
}
#endif

#endif /* SDRTF_PRV_GUARD_H */

/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/