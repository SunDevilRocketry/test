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

/* For TIM_PWM_Start in servo init*/
void MOCK_hal_init();

void MOCK_HAL_Status_Return
    (
    HAL_StatusTypeDef statusToReturn
    );

void MOCK_HAL_TIM_PWM_Start
    (
    uint8_t call_number,
    HAL_StatusTypeDef mocked_status
    );

/* General Mocks */
void MOCK_HAL_Status_Return
    (
    HAL_StatusTypeDef statusToReturn
    );