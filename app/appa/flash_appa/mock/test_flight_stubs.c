
#include <stdlib.h>
#include <string.h>
#include "flash.h"
#include "buzzer.h"
#include "led.h"

/* globals */
//HFLASH_BUFFER* pflash_buffer;

/* Test-only globals */
extern uint8_t* mock_flash_memory;

/* functions */
void reset_stubs
	(
		void
	)
{
// this still needs to be set up
}

/* Sets the LED to a color from the LED_COLOR_CODES enum */
void led_set_color(LED_COLOR_CODES color) {}

/* Beep the flight computer buzzer a specified number of times (blocking) */
BUZZ_STATUS buzzer_multi_beeps
	(
	uint32_t beep_duration, 		/* Length of beep in milliseconds */
	uint32_t time_between_beeps,	/* How long to wait between beeps in ms */
	uint8_t	 num_beeps 				/* How many times to repeat */
	)
{
return BUZZ_OK;
}

/* Check if the flash chip is ready for write operations */
bool flash_is_flash_busy
	(
	void
	)
{
return FLASH_READY;
}

/* Write bytes from a flash buffer to the external flash */
FLASH_STATUS flash_write
    (
	HFLASH_BUFFER* pflash_handle
    )
{
/* Trying to copy the flash buffer into the mock flash memory */
/* seg fault */
// uint8_t address = mock_flash_memory + pflash_handle->address;
// memcpy(address, pflash_handle->pbuffer, pflash_handle->num_bytes);

return FLASH_OK;
}

/* Read a specified number of bytes using a flash buffer */
FLASH_STATUS flash_read
    (
	HFLASH_BUFFER* pflash_handle,
    uint32_t       num_bytes
    )
{
return FLASH_OK;
}

/* Erase the entire flash chip */
FLASH_STATUS flash_erase
    (
    HFLASH_BUFFER* pflash_handle	
    )
{
return FLASH_OK;
}

/* Erase a 32kB block of flash */
FLASH_STATUS flash_block_erase
	(
	FLASH_BLOCK      flash_block_num, 
	FLASH_BLOCK_SIZE size
	)
{
/* Do something with the mock flash memory */
uint8_t* flash_addr = &mock_flash_memory; /* Address of block to erase */
size_t block_size;

switch( size )
	{
	case FLASH_BLOCK_4K:
		{
		block_size = 0x1000;
		flash_addr   += flash_block_num*(0x1000);
		break;
		}

	case FLASH_BLOCK_32K:
		{
		block_size = 0x8000;
		flash_addr   += flash_block_num*(0x8000);
		break;
		}

	case FLASH_BLOCK_64K:
		{
		block_size = 0x10000;
		flash_addr   += flash_block_num*(0x10000);
		}

		/* Error check */
		if ( flash_block_num >= FLASH_BLOCK_8 )
			{
			return FLASH_ADDR_OUT_OF_BOUNDS;
			}
		break;
	}

// this doesn't work
// memset(flash_addr, 0, block_size);

return FLASH_OK;

}