#include "fin_calib.h"

extern int do_fail;

USB_STATUS finCalibration(uint8_t *signalIn) { 
    if (do_fail == 1) {
        return USB_FAIL;
    } else {
        return USB_OK; 
    }
}