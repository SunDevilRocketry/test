#ifndef STUBS /* recursive inclusion guard */

/* Macros */

/* 512kB flash memory */
#define FLASH_MEMORY_SIZE 0x80000
#define FLASH_ERASE_VALUE 255

/* functions */
void reset_stubs
    (
    void
    );

void reset_mock_flash
	(
	void
	);

#endif