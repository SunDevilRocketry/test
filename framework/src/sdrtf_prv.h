/*******************************************************************************
*
* FILE: 
* 		sdrtf_prv.h
*
* DESCRIPTION: 
* 		The Sun Devil Rocketry embedded test framework. Do not include this header
*       in your tests.
*                                                                              
* COPYRIGHT:                                                                   
*       Copyright (c) 2025 Sun Devil Rocketry.                                 
*       All rights reserved.                                                   
*                                                                              
*       This software is licensed under terms that can be found in the LICENSE 
*       file in the root directory of this software component.                 
*       If no LICENSE file comes with this software, it is covered under the   
*       BSD-3-Clause.                                                          
*                                                                              
*       https://opensource.org/license/bsd-3-clause                            
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
#define TEST_MAX_SUPPORTED_GCC_VERSION 15

#define TEST_MIN_SUPPORTED_GCOVR_VERSION 8
#define TEST_MAX_SUPPORTED_GCOVR_VERSION 8

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