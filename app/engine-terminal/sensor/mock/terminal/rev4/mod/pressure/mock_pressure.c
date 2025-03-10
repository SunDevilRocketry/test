/*******************************************************************************
*
* FILE: 
* 		mock_pressure.c
*
* DESCRIPTION: 
*      Contains mock/stub functions for functions in pressure.c
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdint.h>

/*------------------------------------------------------------------------------
 Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "pressure.h"

/*------------------------------------------------------------------------------
 Global Variables 
------------------------------------------------------------------------------*/

/* MOCK return values */
static uint32_t        return_val__pressure_get_pt_reading = 0;
static PRESSURE_STATUS return_val__pressure_poll_pts       = 0;
static uint8_t         return_val__pressure_get_gain       = 0;
static uint16_t        return_val__mux_map                 = 0;
static PRESSURE_STATUS return_val__sample_adc_poll         = 0;
static uint16_t        return_val__amplifier_gain_map      = 0;

/* Amplifier gain settings */
static uint8_t         pt_gains[] = { 0, 0, 0, 0, 0, 0, 0, 0 } ; 


/*------------------------------------------------------------------------------
 Internal function prototypes 
------------------------------------------------------------------------------*/

/* PT number to GPIO pin butmask mapping */
static inline uint16_t mux_map
	(
    PRESSURE_PT_NUM    pt_num    
    );

/* Sample ADC in polling mode */
static PRESSURE_STATUS sample_adc_poll
	(
    uint16_t     num_samples,
    uint32_t*    psample_buffer
    );

/* Mapping from PT number to amplifer gain GPIO pin bitmask */
static uint16_t amplifier_gain_map
	(
    uint8_t gain_setting 
    );


/*------------------------------------------------------------------------------
 API Functions 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		pressure_get_pt_reading                                                *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Get a single pressure transducer reading                               *
*                                                                              *
*******************************************************************************/
uint32_t pressure_get_pt_reading 
	(
    PRESSURE_PT_NUM pt_num
    )
{
return return_val__pressure_get_pt_reading;
} /* pressure_get_pt_reading */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		pressure_poll_pts                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Get readings from all pressure transducers                             *
*                                                                              *
*******************************************************************************/
PRESSURE_STATUS pressure_poll_pts
	(
    uint32_t* pPT_readings /* array of size NUM_PTS */ 
    )
{
return return_val__pressure_poll_pts;
} /* pressure_poll_pts */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		pressure_set_gain                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Set the amplifier gain for a single pressure transducer                *
*                                                                              *
*******************************************************************************/
void pressure_set_gain
	(
    PRESSURE_PT_NUM pt_num,
    uint8_t         gain
    )
{

} /* pressure_set_gain */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		pressure_set_all_gains                                                 *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Set the amplifier gain for all pressure transducers                    *
*                                                                              *
*******************************************************************************/
void pressure_set_all_gains
	(
    uint8_t gains[] 
    )
{

} /* pressure_set_gains */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		pressure_get_gain                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Get the gain for a single pressure transducer                          *
*                                                                              *
*******************************************************************************/
uint8_t pressure_get_gain
	(
    PRESSURE_PT_NUM pt_num
    )
{
return return_val__pressure_get_gain;
} /* pressure_get_gain */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		pressure_get_all_gains                                                 *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Get the gain for all pressure transducers                              *
*                                                                              *
*******************************************************************************/
void pressure_get_all_gains
	(
    uint8_t* pgains 
    )
{

} /* pressure_get_all_gains */


/*------------------------------------------------------------------------------
 Internal procedures 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		amplifer_gain_map                                                      *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Mapping from pressure transducer number to amplifer gain GPIO pin      *
*       bitmask. ex. gain setting 128 -> PRESSURE_GAIN7_PIN                    * 
*                                                                              *
*******************************************************************************/
static uint16_t amplifier_gain_map
	(
    uint8_t gain_setting 
    )
{
return return_val__amplifier_gain_map;
} /* amplifier_gain_map */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		mux_map                                                                *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Mapping from pressure transducer number to mutliplexor GPIO pin        *
*       bitmask. ex. PTNUM5 -> 101 -> GPIO_PIN_C | GPIO_PIN_A                  * 
*                                                                              *
*******************************************************************************/
static inline uint16_t mux_map
	(
    PRESSURE_PT_NUM    pt_num    
    )
{
return return_val__mux_map;
} /* mux_map */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		sample_adc_poll                                                        *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Sample the pressure transducer ADC a specified number of times in      *
*       polling mode                                                           *
*                                                                              *
*******************************************************************************/
static PRESSURE_STATUS sample_adc_poll
	(
    uint16_t    num_samples,
    uint32_t*   psample_buffer
    )
{
return return_val__sample_adc_poll;
} /* sample_adc_poll */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/
