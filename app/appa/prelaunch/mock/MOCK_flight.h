#ifndef MOCK_FLIGHT_H
#define MOCK_FLIGHT_H

#include <stdint.h>
#include <stddef.h>
#include "main.h"

//extern FLIGHT_COMP_STATE_TYPE flight_computer_state;

typedef enum IGN_STATUS
{
IGN_OK               = 0x40, /* Cont status takes up first 64 values */
IGN_SUCCESS          = 0x41,
IGN_EMATCH_CONT_FAIL = 0x42, 
IGN_POWER_FAIL       = 0x43, 
IGN_FAIL             = 0x44,
IGN_SWITCH_FAIL      = 0x45,
IGN_MAIN_CONT_FAIL   = 0x46,
IGN_MAIN_FAIL        = 0x47,
IGN_DROGUE_CONT_FAIL = 0x48, 
IGN_DROGUE_FAIL      = 0x49,
IGN_UNRECOGNIZED_CMD = 0x4A
} IGN_STATUS;

void flight_loop(uint8_t *gps_mesg_byte, FLASH_STATUS *flash_status, HFLASH_BUFFER *flash_handle, uint32_t *flash_address, SENSOR_STATUS *sensor_status);

#endif