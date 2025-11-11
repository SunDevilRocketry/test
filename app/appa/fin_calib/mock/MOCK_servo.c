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

uint8_t motor_snap_to_bound(uint8_t angle, uint8_t upper, uint8_t lower)
{
    return angle;
}