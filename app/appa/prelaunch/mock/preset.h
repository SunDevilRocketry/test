#ifndef MOCK_PRESET_H
#define MOCK_PRESET_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "usb.h"
#include "main.h"

//extern PRESET_DATA preset_data;

FLASH_STATUS write_preset(HFLASH_BUFFER* pflash_handle, PRESET_DATA* preset_data_ptr, uint32_t* flash_address);
//FLASH_STATUS preset_cmd_execute(uint8_t* subcommand_code, HFLASH_BUFFER* flash_handle, uint32_t* flash_address);
FLASH_STATUS flash_cmd_execute(uint8_t subcommand_code, HFLASH_BUFFER* pflash_handle);
//bool check_config_validity(PRESET_DATA* preset_data_ptr);
uint32_t crc32(const uint8_t *data, size_t len);

#endif
