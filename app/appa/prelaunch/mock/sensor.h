#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H

#include <stdint.h>
#include <stddef.h>
#include "main.h"

SENSOR_STATUS sensor_cmd_execute(uint8_t subcommand);

#endif