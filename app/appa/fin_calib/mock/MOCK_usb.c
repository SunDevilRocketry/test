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

/*------------------------------------------------------------------------------
Project Includes
------------------------------------------------------------------------------*/
#include "main.h"
#include "usb.h"
#include "test.h"

/*------------------------------------------------------------------------------
Standard Includes
------------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*------------------------------------------------------------------------------
Global Variables
------------------------------------------------------------------------------*/
/* Queue of simulated USB transmissions, defined in test_fin_calib.c */
extern uint8_t* usb_queue;
extern int  usb_pos;

/* Value for usb_detect to return */
extern bool usb_detect_value;

/*------------------------------------------------------------------------------
Mock Functions
------------------------------------------------------------------------------*/
bool usb_detect
	(
	void
	)
{
    return usb_detect_value;
}

USB_STATUS usb_receive 
	(
	void*    rx_data_ptr,
	size_t   rx_data_size,
	uint32_t timeout
	)
{
	uint8_t* result = rx_data_ptr;

	/* If you get an out-of-bounds error here, it's probably because you forgot to
	include an EXIT command in usb_queue or reset
	usb_pos to 0. */
	*result = usb_queue[ usb_pos ]; 

	usb_pos++;
	
	return USB_OK;
}
