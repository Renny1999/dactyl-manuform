#include "4x6.h"

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case LT(1,KC_ENT):
        return 100;

      default:
        return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1, KC_ENT):
            // Immediately select the hold action when another key is pressed.
            return true;

        // case LT(2, KC_SPACE):
        //     // Immediately select the hold action when another key is pressed.
        //     return true;

        case LT(3, KC_SPACE):
            // Immediately select the hold action when another key is pressed.
            return true;

        case LSFT_T(KC_ENT):
            // Immediately select the hold action when another key is pressed.
          return true;

        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    // Only the mod-taps (HRMs) get permissive hold. Layer-taps are left alone,
    // so space -> letter rolls on LT(2, KC_SPC) never trigger layer 2.
    return IS_QK_MOD_TAP(keycode);
}

// Chordal hold: a HRM only resolves as hold when the other key is on the
// opposite hand. Rows 0-4 are the left half, rows 5-9 the right half.
// Thumb cluster keys are '*' (exempt), so thumb layer-taps keep working with
// same-side keys, and HRM + same-side thumb key still allows a hold.
char chordal_hold_handedness(keypos_t key) {
    bool left = key.row < MATRIX_ROWS / 2;
    uint8_t row = left ? key.row : key.row - MATRIX_ROWS / 2;

    if (row == 4) {
        return '*';  // lower thumb cluster
    }
    if (row == 3 && (left ? key.col >= 4 : key.col <= 1)) {
        return '*';  // main thumb keys
    }
    return left ? 'L' : 'R';
}
