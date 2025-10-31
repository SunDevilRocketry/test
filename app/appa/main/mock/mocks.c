/*******************************************************************************
*
* FILE: 
*      mocks.c
*
* DESCRIPTION: 
*      Mocks and stubs for the entry point procedure.
*
*******************************************************************************/

#include "stm32h7xx_hal.h"
#include "flash.h"
#include "baro.h"
#include "imu.h"
#include "servo.h"
#include "ignition.h"
#include "common.h"
#include "main.h"
#include "led.h"

HAL_StatusTypeDef HAL_Init(void)
{
return HAL_OK;
}

void SystemClock_Config
	(
	void
	)
{
// stubbed out
}

void PeriphCommonClock_Config(void)
{
// stub
}

void GPIO_Init()
{
// stub
}

void USB_UART_Init
	(
	void
	)
{
// stub
}

void GPS_UART_Init()
{
// stub
}

void Baro_I2C_Init
	(
	void
	)
{
// stub
}

void IMU_GPS_I2C_Init()
{
// stub
}

void FLASH_SPI_Init()
{
// stub
}

void BUZZER_TIM_Init()
{
// stub
}

void SD_SDMMC_Init()
{
// stub
}

void PWM4_TIM_Init()
{
// stub
}

void PWM123_TIM_Init()
{
// stub
}

FLASH_STATUS flash_init 
	(
	HFLASH_BUFFER* pflash_handle  /* Flash handle */
	)
{
return FLASH_OK;
}

void sensor_init 
	(
	void
	)
{
// stub
}

BARO_STATUS baro_init
	(
	BARO_CONFIG* config_ptr
	)
{
return BARO_OK;
}

IMU_STATUS imu_init 
	(
    IMU_CONFIG* imu_config_ptr /* IMU Configuration */ 
	)
{
return IMU_OK;
}

SERVO_STATUS servo_init
    (
    void
    )
{
return SERVO_OK;
}

bool ign_switch_cont()
{
return false;
}

FLASH_STATUS read_preset
	(
	HFLASH_BUFFER* pflash_handle,
	PRESET_DATA*   preset_data_ptr,
	uint32_t*	   address
	)
{
return FLASH_OK;
}

void error_fail_fast
	(
	volatile ERROR_CODE error_code
	)
{
// stub
}

void led_set_color
	(
	LED_COLOR_CODES color
	)
{
// stub
}

void appa_fsm
    (
    uint8_t firmware_code,
    FLASH_STATUS* flash_status,
    HFLASH_BUFFER* flash_handle,
    uint32_t* flash_address,
    uint8_t* gps_mesg_byte,
    SENSOR_STATUS* sensor_status
    )
{
// stub
}