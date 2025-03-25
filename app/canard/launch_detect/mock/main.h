/*******************************************************************************
*
* FILE: 
*      main.h (MOCK)
*
* DESCRIPTION: 
*      Header file to trick the test into compiling. Also contains mock function
*      definitions.
*
*******************************************************************************/

#include "sdr_pin_defines_A0002.h"
#include "stm32h7xx_hal_uart.h"

#include <stdint.h>

/* launch_detect.c */
void launch_detection(uint8_t* acc_detect_flag);

void MOCK_HAL_Status_Return
    (
    HAL_StatusTypeDef statusToReturn
    );