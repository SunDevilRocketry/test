#include <stdbool.h>
#include "main.h"
#include "ignition.h"

extern int do_switch;
extern int do_drogue;
extern int do_main;

bool ign_switch_cont(void) { 
    if (do_switch == 1) {
        return true;
    } else {
        return false;
    } 
}

bool ign_drogue_cont(void) { 
    if (do_drogue == 1) {
        return true;
    } else {
        return false;
    }
 }
bool ign_main_cont(void) { 
    if (do_main == 1) {
        return true;
    } else {
        return false;
    }
 }