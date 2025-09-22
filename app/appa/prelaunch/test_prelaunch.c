/*******************************************************************************
*
* FILE: 
*      prelaunch.c
*
* DESCRIPTION: 
*      Unit tests for the prelaunch procedure.
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>


/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "sdrtf_pub.h"
#include "main.h"
#include "sensor.h"
#include "imu.h"
#include "test.h"
#include "usb.h"
#include "commands.h"

/*------------------------------------------------------------------------------
Global Variables 
------------------------------------------------------------------------------*/
UART_HandleTypeDef huart4;  /* GPS */
I2C_HandleTypeDef  hi2c1;   /* Baro sensor    */
I2C_HandleTypeDef  hi2c2;   /* IMU and GPS    */
SENSOR_DATA sensor_data;
PRESET_DATA preset_data;
FLIGHT_COMP_STATE_TYPE flight_computer_state;

/*------------------------------------------------------------------------------
Local Variables
------------------------------------------------------------------------------*/
/* breaking control flow */
int jmp_val; 
jmp_buf env_buffer;
int do_jump = 0; // All mocks check do_jump == 1 before jumping
int do_fake_checksum = 0;
int do_fail = 0;
int do_detect = 0;
int do_switch = 0;
int do_receive = 0;
int call_count = 0;
int do_drogue = 1;
int do_main = 1;
int skip_loop = 0;

/*------------------------------------------------------------------------------
Macros
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Procedures: Tests // Define the tests used here
------------------------------------------------------------------------------*/
void test_check_config_validity() {
	PRESET_DATA preset_data_check_config;

	/* Test One */
	// preset_data_check_config.config_settings.enabled_features = 255u;
	// preset_data_check_config.config_settings.enabled_features |= ACTIVE_PITCH_YAW_CONTROL_ENABLED;
	static bool end_jmp_back = false;

	// TODO: Fix this stack overflowing
	// do_jump = 1;
	// jmp_val = setjmp(env_buffer); // Set jump back location
	// if (!end_jmp_back) {
	// 	end_jmp_back = true;
		
	// 	bool test_one = check_config_validity(&preset_data_check_config);

	// 	_test_assert(ASSERT_TYPE_EQ, "Caught invalid config (This test jumps out of an infinite loop)", test_one, __LINE__, __FILE__);
	// }
	/* -------- */

	/* Test Two */
	preset_data_check_config.config_settings.enabled_features = 0u;
	end_jmp_back = false;

	jmp_val = setjmp(env_buffer); // Set jump back location
	if (!end_jmp_back) {
		end_jmp_back = true;
		
		bool test_two = check_config_validity(&preset_data_check_config);

		_test_assert(ASSERT_TYPE_EQ, "Verified config", test_two, __LINE__, __FILE__);
	}
	/* -------- */
}

void test_preset_cmd_execute() {
	HFLASH_BUFFER* flash_handle;
	uint32_t* flash_address;

	/* PRESET_UPLOAD */
	uint8_t subcommand_code = 0x01;
	FLASH_STATUS test_one = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Working Upload Preset with not matching checksum", test_one, FLASH_OK, __LINE__, __FILE__);
	
	do_fake_checksum = 1;
	FLASH_STATUS test_two = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Working Upload Preset with matching checksum", test_two, FLASH_OK, __LINE__, __FILE__);
	
	/* PRESET DOWNLOAD */
	subcommand_code = 0x02;
	FLASH_STATUS test_three = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Working Download Preset", test_three, FLASH_OK, __LINE__, __FILE__);
	
	do_fail = 1;
	FLASH_STATUS test_four = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Failing Download Preset", test_four, FLASH_FAIL, __LINE__, __FILE__);
	
	/* PRESET VERIFY */
	do_fail = 0;
	subcommand_code = 0x03;
	FLASH_STATUS test_five = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Working Verify Preset", test_five, FLASH_OK, __LINE__, __FILE__);

	do_fail = 1;
	FLASH_STATUS test_six = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Working Verify Preset", test_six, FLASH_OK, __LINE__, __FILE__);

	/* UKNOWN SUBCOMMAND */
	subcommand_code = 0x04;
	FLASH_STATUS test_seven = preset_cmd_execute(&subcommand_code, &flash_handle, &flash_address);
	_test_assert_sint(ASSERT_TYPE_EQ, "Unrecognized command code", test_seven, FLASH_FAIL, __LINE__, __FILE__);
}

void test_prelaunch_terminal() {
	uint8_t firmware_code = 0x00;
	FLASH_STATUS* flash_status;
	HFLASH_BUFFER* flash_handle;
	uint32_t* flash_address;
	uint8_t* gps_msg_byte;
	SENSOR_STATUS* sensor_status;

	/* Test One */
	USB_STATUS test_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting no USB and do not enter flight mode", test_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	/* -------- */

	/* Test Connect */
	do_detect = 1;
	usb_receive_steps_count = 1;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = CONNECT_OP};
	USB_STATUS test_connect_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending connect op, and do not enter flight mode", test_connect_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	/* ------------ */

	/* Test Sensor */
	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = SENSOR_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_OK};
	USB_STATUS test_sensor_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending sensor op, and do not enter flight mode", test_sensor_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	
	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = SENSOR_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	USB_STATUS test_sensor_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending sensor op, usb failing, and do not enter flight mode", test_sensor_two, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	/* ----------- */

	/* Test Fin */
	do_detect = 1;
	do_fail = 0;
	usb_receive_steps_count = 1;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = FIN_OP};
	USB_STATUS test_fin_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending fin op, and do not enter flight mode", test_fin_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 1;
	do_fail = 1;
	usb_receive_steps_count = 1;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = FIN_OP};
	USB_STATUS test_fin_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending fin op, failing usb, failing flash, and do not enter flight mode", test_fin_two, USB_FAIL, __LINE__, __FILE__);
	call_count = 0;
	do_fail = 0;
	/* -------- */

	/* Test Flash */
	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = FLASH_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_OK};
	USB_STATUS test_flash_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending flash op, and do not enter flight mode", test_flash_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = FLASH_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	USB_STATUS test_flash_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	// TODO: verify USB_OK is correct. I think it is because transmit passes after?
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending flash op, failing usb, and do not enter flight mode", test_flash_two, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = FLASH_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	do_fail = 1;
	USB_STATUS test_flash_three = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending flash op, failing usb, failing usb transmit, and do not enter flight mode", test_flash_three, USB_FAIL, __LINE__, __FILE__);
	call_count = 0;
	do_fail = 0;
	/* -------- */

	/* Test Preset */
	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = PRESET_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_OK};
	USB_STATUS test_preset_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending preset op, and do not enter flight mode", test_preset_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	
	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = PRESET_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	USB_STATUS test_preset_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	// TODO: verify USB_OK is correct. I think it is because transmit passes after?
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending preset op, failing usb, and do not enter flight mode", test_preset_two, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = PRESET_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	do_fail = 1;
	USB_STATUS test_preset_three = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending preset op, failing usb, failing usb transmit, and do not enter flight mode", test_preset_three, USB_FAIL, __LINE__, __FILE__);
	call_count = 0;
	do_fail = 0;
	/* ----------- */

	/* Test Servo */
	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = SERVO_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_OK};
	USB_STATUS test_servo_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending servo op, and do not enter flight mode", test_servo_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = SERVO_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	USB_STATUS test_servo_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending servo op, failing usb, and do not enter flight mode", test_servo_two, USB_FAIL, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 1;
	usb_receive_steps_count = 2;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = SERVO_OP};
	usb_receive_steps[1] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = 0x01};
	USB_STATUS test_servo_three = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending servo op, passing servo status, and do not enter flight mode", test_servo_three, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	/* ---------- */

	/* Test Fail USB */
	do_detect = 1;
	usb_receive_steps_count = 1;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = RETURN, .return_val = USB_FAIL};
	USB_STATUS test_fail_usb = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, failing usb, and do not enter flight mode", test_fail_usb, USB_FAIL, __LINE__, __FILE__);
	call_count = 0;
	/* ------------- */

	/* Test Unknown OP */
	do_detect = 1;
	usb_receive_steps_count = 1;
	usb_receive_steps[0] = (USB_RECEIVE_STEP){.action = BUFFER, .buffer_val = 0x09};
	USB_STATUS test_unknown_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Detecting USB, sending unknown op, and do not enter flight mode", test_unknown_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	/* --------------- */

	/* Test Arm Flight Computer */
	do_detect = 0;
	do_switch = 1;
	preset_data.config_settings.enabled_features = 0u;
	USB_STATUS test_arm_fc_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Do not detect USB, enter flight mode, pass config check, do not dual deploy", test_arm_fc_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	// TODO: how to break out the loop and return valid?
	// do_detect = 0;
	// do_switch = 1;
	// preset_data.config_settings.enabled_features = ACTIVE_PITCH_YAW_CONTROL_ENABLED;
	// USB_STATUS test_arm_fc_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	// _test_assert_sint(ASSERT_TYPE_EQ, "Do not detect USB, enter flight mode, fail config check, do not dual deploy", test_arm_fc_two, USB_OK, __LINE__, __FILE__);
	// call_count = 0;

	do_detect = 0;
	do_switch = 1;
	preset_data.config_settings.enabled_features = DUAL_DEPLOY_ENABLED;
	USB_STATUS test_dual_deploy_one = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Do not detect USB, enter flight mode, fail config check, do dual deploy", test_dual_deploy_one, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 0;
	do_switch = 1;
	do_drogue = 0;
	preset_data.config_settings.enabled_features = DUAL_DEPLOY_ENABLED;
	USB_STATUS test_dual_deploy_two = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Do not detect USB, enter flight mode, fail config check, do dual deploy with drogue fail", test_dual_deploy_two, USB_OK, __LINE__, __FILE__);
	call_count = 0;

	do_detect = 0;
	do_switch = 1;
	do_drogue = 1;
	do_main = 0;
	preset_data.config_settings.enabled_features = DUAL_DEPLOY_ENABLED;
	USB_STATUS test_dual_deploy_three = prelaunch_terminal(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	_test_assert_sint(ASSERT_TYPE_EQ, "Do not detect USB, enter flight mode, fail config check, do dual deploy with main fail", test_dual_deploy_three, USB_OK, __LINE__, __FILE__);
	call_count = 0;
	/* -------------------------*/
}

void test_prelaunch_loop() {
	uint8_t firmware_code = 0x00;
	FLASH_STATUS* flash_status;
	HFLASH_BUFFER* flash_handle;
	uint32_t* flash_address;
	uint8_t* gps_msg_byte;
	SENSOR_STATUS* sensor_status;

	skip_loop = 1;
	pre_launch_loop(&firmware_code, &flash_status, &flash_handle, &flash_address, &gps_msg_byte, &sensor_status);
	//_test_assert_sint(ASSERT_TYPE_EQ, "Invalid Config, do not enter loop", fc_state, FC_STATE_INIT, __LINE__, __FILE__);
	skip_loop = 0;

}

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       main			                                   			           *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Set up the testing enviroment, call tests, tear down the testing       *
*		environment															   *
*                                                                              *
*******************************************************************************/
int main
	(
	void
	)
{
/*------------------------------------------------------------------------------
Initialize Memory
------------------------------------------------------------------------------*/
memset( &sensor_data, 0, sizeof( SENSOR_DATA ) );
memset( &preset_data, 0, sizeof( PRESET_DATA ) );
memset( &flight_computer_state, 0, sizeof( FLIGHT_COMP_STATE_TYPE ) );

memset(&env_buffer, 0, sizeof(jmp_buf));

/*------------------------------------------------------------------------------
Test Cases
------------------------------------------------------------------------------*/
unit_test tests[] =
	{
	{ "check config validity", test_check_config_validity },
	//{ "preset cmd execute", test_preset_cmd_execute }, TODO: this is stack overflowing
	{ "prelaunch terminal", test_prelaunch_terminal},
	//{ "prelaunch loop", test_prelaunch_loop}
	};

/*------------------------------------------------------------------------------
Call the framework
------------------------------------------------------------------------------*/
TEST_INITIALIZE_TEST( "prelaunch.c", tests );

} /* main */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/