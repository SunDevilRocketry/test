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
#include "usb.h"

#include <stdbool.h>
#include <stdint.h>

bool usb_detect
	(
	void
	)
{
    return true;
}

USB_STATUS usb_receive 
	(
	void*    rx_data_ptr ,
	size_t   rx_data_size,
	uint32_t timeout
	)
{
	return USB_OK;
}
