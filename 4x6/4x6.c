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

        case LT(3, KC_SPACE):
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

// Chordal hold, limited to the H/E pair: when one of them is held and the
// other is pressed, settle the held key as a tap so "he"/"eh" rolls never
// fire GUI/Shift. Every other chord (e.g. Ctrl+W, Ctrl+L on the same hand)
// resolves normally, so permissive hold applies.
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record,
                      uint16_t other_keycode, keyrecord_t *other_record) {
    switch (tap_hold_keycode) {
        case LGUI_T(KC_H):
            return other_keycode != RSFT_T(KC_E);
        case RSFT_T(KC_E):
            return other_keycode != LGUI_T(KC_H);
        default:
            return true;
    }
}
