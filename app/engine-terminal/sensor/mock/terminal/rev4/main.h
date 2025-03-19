/*******************************************************************************
*
* FILE: 
* 		main.h
*
* DESCRIPTION: 
* 		Processes commands recieved from a host PC, provides fine control over 
*       engine controller hardware resources
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
 Macros  
------------------------------------------------------------------------------*/

/* General MCU HAL related macros */
#define HAL_DEFAULT_TIMEOUT    ( 1 )   /* Default timeout for polling 
                                          operations                          */
#define DEF_BUFFER_SIZE        ( 16 )  /* Default size of buffer arrays       */

/*------------------------------------------------------------------------------
 MCU Pin Assignments                                                          
------------------------------------------------------------------------------*/

/*-------------------------------- Pins --------------------------------------*/

/* LED */
#define STATUS_B_PIN	          GPIO_PIN_12    
#define STATUS_G_PIN              GPIO_PIN_11  
#define STATUS_R_PIN              GPIO_PIN_10  

/* Ignition */
#define FIRE_PIN                  GPIO_PIN_6   
#define E_CONT_PIN                GPIO_PIN_7   
#define NOZ_CONT_PIN              GPIO_PIN_8    
#define SP_CONT_PIN               GPIO_PIN_9   

/* Power */
#define PWR_SRC_PIN               GPIO_PIN_0   

/* External Flash */
#define FLASH_SS_PIN              GPIO_PIN_12  
#define FLASH_SCK_PIN             GPIO_PIN_10 
#define FLASH_MISO_PIN            GPIO_PIN_14
#define FLASH_MOSI_PIN            GPIO_PIN_15
#define FLASH_WP_PIN              GPIO_PIN_12
#define FLASH_HOLD_PIN            GPIO_PIN_13

/* Pressure transducers */
#define PRESSURE_GAIN0_PIN        GPIO_PIN_0
#define PRESSURE_GAIN1_PIN        GPIO_PIN_1
#define PRESSURE_GAIN2_PIN        GPIO_PIN_3
#define PRESSURE_GAIN3_PIN        GPIO_PIN_4
#define PRESSURE_GAIN4_PIN        GPIO_PIN_5
#define PRESSURE_GAIN5_PIN        GPIO_PIN_6
#define PRESSURE_GAIN6_PIN        GPIO_PIN_7
#define PRESSURE_GAIN7_PIN        GPIO_PIN_8
#define PRESSURE_GAIN_ALL_PINS    ( (uint16_t) 0x01FB )
#define PRESSURE_MUXA_PIN         GPIO_PIN_9
#define PRESSURE_MUXB_PIN         GPIO_PIN_10
#define PRESSURE_MUXC_PIN         GPIO_PIN_11
#define PRESSURE_MUX_ALL_PINS     ( (uint16_t) 0x0E00 )

/*-------------------------------- Ports--------------------------------------*/

/* LED */
#define STATUS_GPIO_PORT          GPIOE        

/* Ignition */
#define FIRE_GPIO_PORT            GPIOE        
#define E_CONT_GPIO_PORT          GPIOE        
#define NOZ_CONT_GPIO_PORT        GPIOE        
#define SP_CONT_GPIO_PORT         GPIOE        

/* Power */
#define PWR_SRC_GPIO_PORT         GPIOE        

/* External Flash */
#define FLASH_SS_GPIO_PORT        GPIOB        
#define FLASH_SCK_GPIO_PORT       GPIOB  
#define FLASH_MISO_GPIO_PORT      GPIOB  
#define FLASH_MOSI_GPIO_PORT      GPIOB  
#define FLASH_WP_GPIO_PORT        GPIOD
#define FLASH_HOLD_GPIO_PORT      GPIOD

/* Pressure transducers */
#define PRESSURE_GPIO_PORT        GPIOD
	

/*------------------------------------------------------------------------------
 Exported functions prototypes                                             
------------------------------------------------------------------------------*/
void Error_Handler(void);

void readings_to_bytes();

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
