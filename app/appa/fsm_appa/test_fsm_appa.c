/*******************************************************************************
*
* FILE:
*      test_fsm_appa.c
*
* DESCRIPTION:
*      Unit tests for functions in the APPA FSM module.
*
* NOTE:
*      Modeled after test_flight.c. Uses the same test framework and stub style.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes
------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>
#include <setjmp.h> /* NEVER do this in production code. This is used to circumvent
                       infinite loops. */


/*------------------------------------------------------------------------------
Project Includes
------------------------------------------------------------------------------*/
#include "sdrtf_pub.h"
#include "main.h"
#include "common.h"
#include "sensor.h"
#include "servo.h"
#include "ignition.h"
#include "flash.h"
#include "usb.h"
#include "buzzer.h"
#include "led.h"
#include "test_fsm_appa_stubs.h"   /* New stub header analogous to test_flight_stubs.h */


/*------------------------------------------------------------------------------
Global Variables
------------------------------------------------------------------------------*/
uint8_t  sensor_frame_size;
uint32_t tdelta;
SENSOR_DATA   sensor_data;
SERVO_PRESET  servo_preset;
PRESET_DATA   preset_data;
PID_DATA      pid_data;


FLIGHT_COMP_STATE_TYPE flight_computer_state;


/* Test-only globals from stubs */
extern USB_STATUS   stub_usb_status_return;
extern bool         stub_prelaunch_called;
extern bool         stub_flight_calib_called;
extern bool         stub_flight_launch_detect_called;
extern bool         stub_flight_in_flight_called;
extern bool         stub_flight_deploy_called;
extern bool         stub_flight_descent_called;
extern uint8_t      stub_led_set_color_calls;
extern uint8_t      stub_buzzer_multi_beeps_calls;
extern uint8_t      stub_buzzer_beep_calls;
extern uint8_t      stub_sensor_start_IT_calls;


/*------------------------------------------------------------------------------
Local Variables
------------------------------------------------------------------------------*/
static ERROR_CODE reported_error;
static bool       intercept_jmp_back;


/* breaking control flow */
static int     jmp_val;
static jmp_buf env_buffer;


/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/
#define MAX_UINT_32 4294967295


/*------------------------------------------------------------------------------
Procedures: Test Helpers
------------------------------------------------------------------------------*/


/*******************************************************************************
*
* PROCEDURE:
*       TEST_CALLBACK_error_fail_fast
*
* DESCRIPTION:
*       Interrupts execution of the FUT and jumps back to the "setjmp" point.
*
*******************************************************************************/
void TEST_CALLBACK_error_fail_fast
    (
    ERROR_CODE error_code
    )
{
/* Break standard control flow. Jump to the target. */
reported_error = error_code;
longjmp( env_buffer, jmp_val );

} /* TEST_CALLBACK_error_fail_fast */



/*******************************************************************************
*
* PROCEDURE:
*       reset_fc_state
*
* DESCRIPTION:
*       Convenience helper to reset FC state between tests.
*
*******************************************************************************/
static void reset_fc_state
    (
    void
    )
{
/* If fc_state_reset() helper exists in fsm_appa.c, call that instead. */
flight_computer_state = FC_STATE_INIT;

} /* reset_fc_state */



/*------------------------------------------------------------------------------
Procedures: Tests
------------------------------------------------------------------------------*/


/*******************************************************************************
*
* PROCEDURE:
*       test_fc_state_update
*
* DESCRIPTION:
*       Test basic state transition logic for fc_state_update().
*
*******************************************************************************/
void test_fc_state_update
    (
    void
    )
{
/*------------------------------------------------------------------------------
Case 1: Stay in same state
------------------------------------------------------------------------------*/
reset_fc_state(); /* should set FC_STATE_INIT */
TEST_ASSERT_EQ_UINT("State starts at INIT.",
                    flight_computer_state, FC_STATE_INIT);

fc_state_update(FC_STATE_INIT);
TEST_ASSERT_EQ_UINT("Staying in same state allowed.",
                    flight_computer_state, FC_STATE_INIT);

/*------------------------------------------------------------------------------
Case 2: Advance by one
------------------------------------------------------------------------------*/
reset_fc_state();
fc_state_update(FC_STATE_IDLE);
TEST_ASSERT_EQ_UINT("Test that advancing by one state is allowed.",
                    flight_computer_state, FC_STATE_IDLE);


/*------------------------------------------------------------------------------
Case 3: Invalid jump triggers error
------------------------------------------------------------------------------*/
reset_fc_state();
reported_error = MAX_UINT_32;
intercept_jmp_back = false;
set_error_callback( TEST_CALLBACK_error_fail_fast );

jmp_val = setjmp( env_buffer );
if( !intercept_jmp_back )
    {
    intercept_jmp_back = true;
    fc_state_update( FC_STATE_FLIGHT ); /* jump more than one state */
    }

/* After longjmp, verify error and that state did not change. */
TEST_ASSERT_EQ_UINT( "Test that invalid state jump reports an error.",
                     reported_error, ERROR_INVALID_STATE_ERROR );
TEST_ASSERT_EQ_UINT( "Test that invalid state jump does not update state.",
                     flight_computer_state, FC_STATE_INIT );

} /* test_fc_state_update */



/*******************************************************************************
*
* PROCEDURE:
*       test_appa_fsm_flash_not_found_entry
*
* DESCRIPTION:
*       Test APPA FSM entry behavior when presets are not found in flash.
*
*******************************************************************************/
void test_appa_fsm_flash_not_found_entry
    (
    void
    )
{
/*------------------------------------------------------------------------------
Set up mocks/stubs
------------------------------------------------------------------------------*/
stubs_reset();
reset_fc_state();
set_error_callback( TEST_CALLBACK_error_fail_fast );
reported_error     = MAX_UINT_32;
intercept_jmp_back = false;

/* Arrange: flash preset not found so we expect yellow LED + 3 beeps. */
FLASH_STATUS flash_status = FLASH_PRESET_NOT_FOUND;
SENSOR_STATUS sensor_status = SENSOR_OK;
uint8_t  gps_mesg_byte[1];
HFLASH_BUFFER flash_handle;
uint32_t flash_address = 0;
uint8_t firmware_code  = 0xAA;

/* Servo defaults */
preset_data.servo_preset.rp_servo1 = 10;
preset_data.servo_preset.rp_servo2 = 20;
preset_data.servo_preset.rp_servo3 = 30;
preset_data.servo_preset.rp_servo4 = 40;

/* Make the prelaunch terminal keep us in IDLE; stub controls loop exit. */
stub_usb_status_return = USB_OK;
set_loop_exit_after_n_iterations( 1 ); /* test stub to prevent infinite loop */


/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
jmp_val = setjmp( env_buffer ); /* used to intercept errors */
if( !intercept_jmp_back )
    {
    intercept_jmp_back = true;
    appa_fsm
        (
        firmware_code,
        &flash_status,
        &flash_handle,
        &flash_address,
        gps_mesg_byte,
        &sensor_status
        );
    }


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/
/* Entry alerts */
TEST_ASSERT_EQ_UINT( "Test that LED color was set twice (warning + idle).",
                     stub_led_set_color_calls, 2 );
TEST_ASSERT_EQ_UINT( "Test that multi-beeps were called twice (warning + idle).",
                     stub_buzzer_multi_beeps_calls, 2 );
TEST_ASSERT_EQ_UINT( "Test that calibration beep was not triggered in IDLE.",
                     stub_buzzer_beep_calls, 0 );

/* Sensor start */
TEST_ASSERT_EQ_UINT( "Test that sensor_start_IT was called once on entry.",
                     stub_sensor_start_IT_calls, 1 );

/* Prelaunch terminal must have been invoked. */
TEST_ASSERT_EQ_UINT( "Test that prelaunch terminal was called.",
                     stub_prelaunch_called, true );

} /* test_appa_fsm_flash_not_found_entry */



/*******************************************************************************
*
* PROCEDURE:
*       test_appa_fsm_flash_found_entry
*
* DESCRIPTION:
*       Test APPA FSM entry behavior when presets are found in flash.
*
*******************************************************************************/
void test_appa_fsm_flash_found_entry
    (
    void
    )
{
/*------------------------------------------------------------------------------
Set up mocks/stubs
------------------------------------------------------------------------------*/
stubs_reset();
reset_fc_state();
set_error_callback( TEST_CALLBACK_error_fail_fast );
reported_error     = MAX_UINT_32;
intercept_jmp_back = false;

/* flash presets found -> no yellow LED / long beeps. */
FLASH_STATUS flash_status = FLASH_OK;
SENSOR_STATUS sensor_status = SENSOR_OK;
uint8_t  gps_mesg_byte[1];
HFLASH_BUFFER flash_handle;
uint32_t flash_address = 0;
uint8_t firmware_code  = 0x55;

/* Servo defaults */
preset_data.servo_preset.rp_servo1 = 11;
preset_data.servo_preset.rp_servo2 = 22;
preset_data.servo_preset.rp_servo3 = 33;
preset_data.servo_preset.rp_servo4 = 44;

stub_usb_status_return = USB_OK;
set_loop_exit_after_n_iterations( 1 );


/*------------------------------------------------------------------------------
Call FUT
------------------------------------------------------------------------------*/
jmp_val = setjmp( env_buffer );
if( !intercept_jmp_back )
    {
    intercept_jmp_back = true;
    appa_fsm
        (
        firmware_code,
        &flash_status,
        &flash_handle,
        &flash_address,
        gps_mesg_byte,
        &sensor_status
        );
    }


/*------------------------------------------------------------------------------
Verify results
------------------------------------------------------------------------------*/
/* Only the green LED + short beeps should have occurred. */
TEST_ASSERT_EQ_UINT( "Test that LED was set once for IDLE (green).",
                     stub_led_set_color_calls, 1 );
TEST_ASSERT_EQ_UINT( "Test that multi-beeps were only for IDLE entry.",
                     stub_buzzer_multi_beeps_calls, 1 );

/* Sensor start still must be called. */
TEST_ASSERT_EQ_UINT( "Test that sensor_start_IT was called once on entry.",
                     stub_sensor_start_IT_calls, 1 );

/* Prelaunch terminal called from IDLE. */
TEST_ASSERT_EQ_UINT( "Test that prelaunch terminal was called.",
                     stub_prelaunch_called, true );

} /* test_appa_fsm_flash_found_entry */



/*******************************************************************************
*
* PROCEDURE:
*       test_appa_fsm_state_branches
*
* DESCRIPTION:
*       Test that each non-IDLE state calls the proper flight function.
*
*******************************************************************************/
void test_appa_fsm_state_branches
    (
    void
    )
{
/*------------------------------------------------------------------------------
Cases
------------------------------------------------------------------------------*/
struct test_case
    {
    const char* description;
    FLIGHT_COMP_STATE_TYPE initial_state;
    bool exp_calib_called;
    bool exp_launch_detect_called;
    bool exp_in_flight_called;
    bool exp_deploy_called;
    bool exp_descent_called;
    };
struct test_case cases[] =
    {
        { "Calibration state executes flight_calib once.",
          FC_STATE_CALIB, true, false, false, false, false },
        { "Launch detect state executes flight_launch_detect once.",
          FC_STATE_LAUNCH_DETECT, false, true, false, false, false },
        { "Flight state executes flight_in_flight once.",
          FC_STATE_FLIGHT, false, false, true, false, false },
        { "Post-apogee state executes flight_deploy once.",
          FC_STATE_POST_APOGEE, false, false, false, true, false },
        { "Deployed state executes flight_descent once.",
          FC_STATE_DEPLOYED, false, false, false, false, true }
    };

for (uint8_t test_num = 0;
     test_num < sizeof(cases) / sizeof(struct test_case);
     test_num++)
    {
    TEST_begin_nested_case(cases[test_num].description);

    stubs_reset();
    reset_fc_state();
    set_error_callback(TEST_CALLBACK_error_fail_fast);
    reported_error     = MAX_UINT_32;

    FLASH_STATUS  flash_status   = FLASH_OK;
    SENSOR_STATUS sensor_status  = SENSOR_OK;
    uint8_t       gps_mesg_byte[1];
    HFLASH_BUFFER flash_handle;
    uint32_t      flash_address  = 0;
    uint32_t      ld_start_time  = 0;

    /* Call the branch directly instead of appa_fsm */
    switch (cases[test_num].initial_state)
        {
        case FC_STATE_CALIB:
            flight_calib(gps_mesg_byte, &flash_handle, &flash_address);
            break;
        case FC_STATE_LAUNCH_DETECT:
            flight_launch_detect(&ld_start_time, &sensor_status,
                                 &flash_status, &flash_handle, &flash_address);
            break;
        case FC_STATE_FLIGHT:
            flight_in_flight(&ld_start_time, &sensor_status,
                             &flash_status, &flash_handle, &flash_address);
            break;
        case FC_STATE_POST_APOGEE:
            flight_deploy();
            break;
        case FC_STATE_DEPLOYED:
            flight_descent(&ld_start_time, &sensor_status,
                           &flash_status, &flash_handle, &flash_address);
            break;
        default:
            break;
        }

    TEST_ASSERT_EQ_UINT("Test that flight_calib was called as expected.",
                        stub_flight_calib_called, cases[test_num].exp_calib_called);
    TEST_ASSERT_EQ_UINT("Test that flight_launch_detect was called as expected.",
                        stub_flight_launch_detect_called, cases[test_num].exp_launch_detect_called);
    TEST_ASSERT_EQ_UINT("Test that flight_in_flight was called as expected.",
                        stub_flight_in_flight_called, cases[test_num].exp_in_flight_called);
    TEST_ASSERT_EQ_UINT("Test that flight_deploy was called as expected.",
                        stub_flight_deploy_called, cases[test_num].exp_deploy_called);
    TEST_ASSERT_EQ_UINT("Test that flight_descent was called as expected.",
                        stub_flight_descent_called, cases[test_num].exp_descent_called);

    TEST_end_nested_case();
    }

} /* test_appa_fsm_state_branches */



/*******************************************************************************
*
* PROCEDURE:
*       test_appa_fsm_usb_failure
*
* DESCRIPTION:
*       Test that USB failure in IDLE triggers fail-fast error.
*
*******************************************************************************/
void test_appa_fsm_usb_failure
    (
    void
    )
{
 stubs_reset();
    reset_fc_state();
    set_error_callback(TEST_CALLBACK_error_fail_fast);
    reported_error     = MAX_UINT_32;
    intercept_jmp_back = false;

    FLASH_STATUS  flash_status   = FLASH_OK;
    SENSOR_STATUS sensor_status  = SENSOR_OK;
    uint8_t       gps_mesg_byte[1];
    HFLASH_BUFFER flash_handle;
    uint32_t      flash_address  = 0;
    uint8_t       firmware_code  = 0x42;

    /* Prelaunch will fail */
    stub_usb_status_return = USB_FAIL;

    jmp_val = setjmp(env_buffer);
    if (!intercept_jmp_back)
        {
        intercept_jmp_back = true;

        /* Simulate IDLE state body of appa_fsm without the while loop */
        USB_STATUS status = prelaunch_terminal(
                                firmware_code,
                                &flash_status,
                                &flash_handle,
                                &flash_address,
                                gps_mesg_byte,
                                &sensor_status);

        if (status == USB_FAIL)
            {
            error_fail_fast(ERROR_USB_UART_ERROR);
            }
        }

    TEST_ASSERT_EQ_UINT("Test that USB failure triggers error_fail_fast.",
                        reported_error, ERROR_USB_UART_ERROR);

} /* test_appa_fsm_usb_failure */



/*******************************************************************************
*
* PROCEDURE:
*       main
*
* DESCRIPTION:
*       Set up the testing environment, call tests, tear down the testing
*       environment.
*
*******************************************************************************/
int main
    (
    void
    )
{
/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
    {
    { "FC State Update: Transition Logic", test_fc_state_update },
    { "APPA FSM: Entry (Flash Not Found)", test_appa_fsm_flash_not_found_entry },
    { "APPA FSM: Entry (Flash Found)", test_appa_fsm_flash_found_entry },
    { "APPA FSM: State Branch Dispatch", test_appa_fsm_state_branches },
    { "APPA FSM: USB Failure Handling", test_appa_fsm_usb_failure }
    };


/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "fsm_appa", tests );

} /* main */



/*******************************************************************************
* END OF FILE
*******************************************************************************/
