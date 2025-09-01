#include "flash.h"
#include "buzzer.h"
#include "led.h"

/* globals */

/* functions */

/* Sets the LED to a color from the LED_COLOR_CODES enum */
void led_set_color
	(
	LED_COLOR_CODES color
	)
{
    
}

/* Beep the flight computer buzzer a specified number of times (blocking) */
BUZZ_STATUS buzzer_multi_beeps
	(
	uint32_t beep_duration, 		/* Length of beep in milliseconds */
	uint32_t time_between_beeps,	/* How long to wait between beeps in ms */
	uint8_t	 num_beeps 				/* How many times to repeat */
	)
{

}

/* Check if the flash chip is ready for write operations */
bool flash_is_flash_busy
	(
	void
	)
{

}

/* Write bytes from a flash buffer to the external flash */
FLASH_STATUS flash_write
    (
	HFLASH_BUFFER* pflash_handle
    )
{

}

/* Read a specified number of bytes using a flash buffer */
FLASH_STATUS flash_read
    (
	HFLASH_BUFFER* pflash_handle,
    uint32_t       num_bytes
    )
{
    
}

/* Erase the entire flash chip */
FLASH_STATUS flash_erase
    (
    HFLASH_BUFFER* pflash_handle	
    )
{

}

/* Erase a 32kB block of flash */
FLASH_STATUS flash_block_erase
	(
	FLASH_BLOCK      flash_block_num, 
	FLASH_BLOCK_SIZE size
	)
{

}