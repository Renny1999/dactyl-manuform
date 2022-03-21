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
        // case LT(2, KC_SPACE):
        //     // Immediately select the hold action when another key is pressed.
        //     return true;
        case LT(3, KC_SPACE):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
