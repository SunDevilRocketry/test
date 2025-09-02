/*******************************************************************************
*
* FILE: 
*      MOCK_usb.c (MOCK)
*
* DESCRIPTION: 
*      Mocked source file. Contains empty function prototypes for USB to trick
*      tests into compiling.
*
*******************************************************************************/

#include "main.h"

#include <stdbool.h>

bool usb_detect
	(
	void
	)
{
    return true;
}