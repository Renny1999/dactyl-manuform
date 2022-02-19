#include "4x6.h"
#include "stdint.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_SPACE):
            // Immediately select the hold action when another key is pressed.
            return true;
        case LT(2, KC_SPACE):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

uint16_t last = 0;
uint16_t last_timer=0;
uint16_t LT_timer= 0;
bool nextPressed = 0;
bool isroll = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record){
    if (keycode == LT(1, KC_SPACE)){
        if (record -> event.pressed) {
            last = keycode; 
            LT_timer = timer_read();
        }else {
            LT_timer = 0;
        }
        return true;
    }

    if(last != LT(1, KC_SPACE)){
        last = keycode;
        return true;
    }
    /*
     * the last key was the LT key. 
     * in this case, detect finger roll and immediately fire the key after LT
     * */
    
    if (LT_timer == 0) {
        return true;
    }
    if (record->event.presssd){
        // record the time
        last_timer=timer_read();
        // check if this is a mod roll
        if(LT_timer > 0 && timer_elapsed(LT_timer) < TAPPING_TERM) {
            // this is a mod roll
            isroll = true;
        } else {
            isroll = false; 
            return true;
        }
    }else {
        // if LT is not yet released
        if (LT_timer != 0) {
            // in this case, act normally
            last_timer = 0;
            return true;
        }else{
            if (isroll) {
                // LT is released, and it's a finger roll:
                // in this case, do the tap action
                register_code (keycode);
                unregister_code (keycode);
                last = keycode;
                last_timer=0;
            }
        }
            
    }
    
}

