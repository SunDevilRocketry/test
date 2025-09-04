#ifndef MOCK_USB_H
#define MOCK_USB_H

#include <stddef.h>
#include <stdint.h>

typedef enum {
    USB_OK = 0
} USB_STATUS;

USB_STATUS usb_receive(void *var0, size_t var1, int var2);
USB_STATUS usb_transmit(void *var0, size_t var1, int var3);
USB_STATUS finCalibration(uint8_t* var0);

#endif