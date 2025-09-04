/*******************************************************************************
*
* FILE: 
*      MOCK_servo.c (MOCK)
*
* DESCRIPTION: 
*      Mocked source file. Contains empty function prototypes for servo to trick
*      tests into compiling.
*
*******************************************************************************/

#include "servo.h"

void motor_drive
    (
    SERVO_ID servo,
    uint8_t angle
    )
{
    return;
}