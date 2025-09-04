#include "preset.h"

//PRESET_DATA preset_data;

FLASH_STATUS write_preset(HFLASH_BUFFER* flash_handle, PRESET_DATA* preset, uint32_t* flash_address) { return FLASH_OK; }
//FLASH_STATUS preset_cmd_execute(uint8_t* subcommand_code, HFLASH_BUFFER* flash_handle, uint32_t* flash_address) { return FLASH_OK; }
FLASH_STATUS flash_cmd_execute(uint8_t flash_subcommand, HFLASH_BUFFER* pflash_handle) { return FLASH_OK; }
//bool check_config_validity(PRESET_DATA* preset_data_ptr) { return true; }
uint32_t crc32(const uint8_t *data, size_t len) { return 0xFFFFFFFF; }