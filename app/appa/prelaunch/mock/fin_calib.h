#ifndef fin_calib_h
#define fin_calib_h

#include <stdint.h>
#include "main.h"
#include "usb.h"
#include "servo.h"
#include "led.h"

USB_STATUS finCalibration(uint8_t *signalIn);

#endif