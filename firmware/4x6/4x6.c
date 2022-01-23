#include "4x6.h"
#include "stdint.h"


#define LEFT 1
#define RIGHT 2

#define HOLD_THRESHOLD 150

#define ELEMENT_0   1
#define ELEMENT_1   2
#define ELEMENT_2   4
#define ELEMENT_3   8
#define ELEMENT_4   16
#define ELEMENT_5   32
#define ELEMENT_6   64      
#define ELEMENT_7   128
#define ELEMENT_8   256
#define ELEMENT_9   512


static uint8_t mods = 0;

// indicates if the actual modifier key is presssed or not
// this is not useful at the moment
static uint8_t realmods = 0;

static uint16_t pending = 0;

#define WAIT_HT(col) { \
    switch (col) {\
        case 0:\
            pending |=  ELEMENT_0;\
            break;\
        case 1:\
            pending |=  ELEMENT_1;\
            break;\
        case 2:\
            pending |=  ELEMENT_2;\
            break;\
        case 3:\
            pending |=  ELEMENT_3;\
            break;\
        case 4:\
            pending |=  ELEMENT_4;\
            break;\
        case 5:\
            pending |=  ELEMENT_5;\
            break;\
        case 6:\
            pending |=  ELEMENT_6;\
            break;\
        case 7:\
            pending |=  ELEMENT_7;\
            break;\
        case 8:\
            pending |=  ELEMENT_8;\
            break;\
        case 9:\
            pending |=  ELEMENT_9;\
            break;\
    }\
} while (0)

#define UNWAIT(col) { \
    switch (col) {\
        case 0:\
            pending &=  ~ELEMENT_0;\
            break;\
        case 1:\
            pending &=  ~ELEMENT_1;\
            break;\
        case 2:\
            pending &=  ~ELEMENT_2;\
            break;\
        case 3:\
            pending &=  ~ELEMENT_3;\
            break;\
        case 4:\
            pending &=  ~ELEMENT_4;\
            break;\
        case 5:\
            pending &=  ~ELEMENT_5;\
            break;\
        case 6:\
            pending &=  ~ELEMENT_6;\
            break;\
        case 7:\
            pending &=  ~ELEMENT_7;\
            break;\
        case 8:\
            pending &=  ~ELEMENT_8;\
            break;\
        case 9:\
            pending &=  ~ELEMENT_9;\
            break;\
    }\
} while (0)

static struct column_event {
    uint16_t key_timer;
    uint16_t keycode;
    uint16_t mod;
    uint8_t shift;
    uint8_t side;
} e[11];

static uint8_t next_key = 0;
static uint8_t prev_key = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        //case KC_A:
        //   mod_roll(record, LEFT, 0, KC_A, 0);
        //    return false;
        //   break;

        case KC_R:
            mod_roll(record, LEFT, KC_LCTL, KC_R, 1);
            return false;
            break;
        case KC_S:
            mod_roll(record, LEFT,KC_LALT, KC_S, 2);
            return false;
            break;

        case KC_T:
            mod_roll(record, LEFT, KC_LSFT, KC_T, 3);
            return false;
            break;
        case KC_N:
            mod_roll(record, LEFT, KC_RSFT, KC_N, 6);
            return false;
            break;

        case KC_E:
            mod_roll(record, RIGHT,KC_LALT, KC_E, 7);
            return false;
            break;
        case KC_I:
            mod_roll(record, RIGHT,KC_LCTL, KC_I, 8);
            return false;
            break;

        //case KC_O:
        //    mod_roll(record, LEFT, 0, KC_O, 9);
        //    return false;
        //    break;
        
        // special cases for the actual modifier keys
        case KC_LCTL:
            if(record -> event.pressed) {
                realmods |= MOD_BIT(keycode);
            }else{
                realmods &= ~(MOD_BIT(keycode));
            }
            return true;
            break;
        case KC_LGUI:
            if(record -> event.pressed) {
                realmods |= MOD_BIT(keycode);
            }else{
                realmods &= ~(MOD_BIT(keycode));
            }
            return true;
            break;
        case KC_LALT:
            if(record -> event.pressed) {
                realmods |= MOD_BIT(keycode);
            }else{
                realmods &= ~(MOD_BIT(keycode));
            }
            return true;
            break;
        case KC_RCTL:
            if(record -> event.pressed) {
                realmods |= MOD_BIT(keycode);
            }else{
                realmods &= ~(MOD_BIT(keycode));
            }
            return true;
            break;
        case KC_RGUI:
            if(record -> event.pressed) {
                realmods |= MOD_BIT(keycode);
            }else{
                realmods &= ~(MOD_BIT(keycode));
            }
            return true;
            break;
        case KC_RALT:
            if(record -> event.pressed) {
                realmods |= MOD_BIT(keycode);
            }else{
                realmods &= ~(MOD_BIT(keycode));
            }
            return true;
            break;
        
        default:
            mod_roll(record, 0, 0, keycode, 10);
            return true;
            break;
    }
    return true;
}


void clear_event(void){
    int i;
    for (i = 0; i < 10; i++){
        e[i].key_timer = 0;
    }
}

/* takes care of key presses and releases
* for normal keys (tap only keys), this function does not perform the actual
* key registering. 
* This is because if we register the key press here, press and holding down 
* the key will only input one character, which is NOT what we want.
* We want press and hold to repeatedly input the character.
*/
void mod_roll (keyrecord_t *record, uint8_t side,
        uint16_t modifier, uint16_t keycode, uint8_t column) {

    if (record -> event.pressed) {
        e[column].key_timer = timer_read();
        e[column].keycode   = keycode;
        e[column].side      = side;
        e[column].mod      = modifier;
        prev_key            = next_key; 
        next_key            = column; 

        if (modifier) {
            // this key is a is a HRM, set pending
            WAIT_HT(column);
        }
        // here, we need to see if any pending keys can become modifiers
        if (pending) {
            int i;
            for(i = 0; i < 10; i++) {
                if((e[i].key_timer != 0) && (timer_elapsed(e[i].key_timer) >= HOLD_THRESHOLD)) {
                    // activate the modifier and stop their waiting
                    register_modifier(e[i].mod);
                    UNWAIT(i);
                }
            }
        }


        if(column != prev_key &&    /* skip if the same homerow modifier is 
                                     * tapped twice
                                     */
           e[prev_key].mod != 0 && 
           e[prev_key].key_timer != 0 ){
            // the previous key is a modifier key and its not released
            /*
             * there are two situation where the previos key should not 
             * become a modifier key when another key is pressd before the 
             * first key is released && before the HOLD_THRESHOLD
             * 
             * 1. current key is a normal key
             * 2. current key results in the same modifier as the first key
             *  if the modifier is already pressed, the key becomes
             *  a normal key                                       
             *  the modifier can be caused by the actual modifier key or the
             *  home row modifier, because the home row modifiers sends key 
             *  modifier keydown events at key press
             * */
             if(timer_elapsed(e[prev_key].key_timer) < HOLD_THRESHOLD) {
                // case 1: current key is a normal key 
                if(modifier == 0){
                        // previous key should not become modifier
                        mod_all(unregister_code);
                        // fire previous key
                        tap_key(e[prev_key].keycode);
                        // pretend the prev key is released
                        e[prev_key].key_timer = 0;
                        e[column].key_timer = 0;
                }else{ 
                    if (e[prev_key].mod == modifier) {
                    // case 2: the two keys will result in the same modifier
                        // previous key should not become modifier
                        mod_all(unregister_code);
                        // fire previous key
                        tap_key(e[prev_key].keycode);
                        /* 
                        * the second key needs to be fired because it is a 
                        * home row modifier, and the default behavior is not 
                        * used
                        */ 
                        tap_key(keycode);
                        // pretend the prev key is released
                        e[prev_key].key_timer = 0;
                        e[column].key_timer = 0;

                        // current key is not waiting
                        UNWAIT(column);
                        return;

                    }
                }
                // the previous key is no longer waiting
                UNWAIT(prev_key);
             } else {
                // the previous key was held down long enough to become a modifier
                //register_modifier(e[prev_key].mod);
                //UNWAIT(prev_key);
             }

        }

        if (modifier) { 
            /*
             * Interesting case:
             *  if a control key is already pressed, and a home row modifier
             *  key for a control key is tapped, the RELEASE event will 
             *  nullify the control key, causing a normal character to be 
             *  registered.
             *  The solution is to check for the modifier at key press
             * */
            if (realmods & MOD_BIT(modifier)) { 
                // pretend the key is tapped 
                tap_key(keycode);
                // pretend the key is released
                e[column].key_timer = 0;
                return;
            }
        }
    }else{
    /*
     * KEY RELEASE
     * */
        if (modifier) {
            if(realmods & MOD_BIT(modifier)) {
                // if the real modifier if pressed down, don't unregister the modifier
            }else {
                // sends modifier key_up event
                unregister_modifier(modifier);
            }
            UNWAIT(column);
        }else{
            return;
        }

        // this release action is skipped because we "pretended" that this
        // key is already released
        if (e[column].key_timer == 0){
            return;
        }

        // if the key is released within its TAPPING_TERM
        // we can determine if this key was involved in a finger roll
        if (timer_elapsed(e[column].key_timer) < HOLD_THRESHOLD) {
            if(e[column].key_timer < e[next_key].key_timer) {
                // this key did not reach mod threshold, but another key was tapped
                // this indicates that there was a finger roll
                // also note that since 
                // e[column].key_timer > 0, 
                // we know that next_key is not released yet
                
                // in a finger roll, the modifiers are disabled
                mod_all(unregister_code);
                // now, we fire the released key
                tap_key(keycode);
                // then, we fire the next_key
                tap_key(e[next_key].keycode);
                // we pretend the next key is released
                e[next_key].key_timer = 0;
            }else {
                // no other key is pressed while the current key is 
                // held down. 
                // simply fire the current key
                tap_key(keycode);
            }
        } else {
            // this key was released after TT, so now it does nothing
        }
        e[column].key_timer = 0;
    }
}


// presses a modifier
void register_modifier(uint16_t keycode){
    register_code(keycode);
    mods |= MOD_BIT(keycode);
}

// releases a modifier
void unregister_modifier(uint16_t keycode){
    unregister_code(keycode);
    mods &= ~(MOD_BIT(keycode));
}

// applies a function to all modifiers
void mod_all(void (*f)(uint8_t)) {
  if (mods & MOD_BIT(KC_LGUI)) { f(KC_LGUI); }
  if (mods & MOD_BIT(KC_LCTL)) { f(KC_LCTL); }
  if (mods & MOD_BIT(KC_LALT)) { f(KC_LALT); }
  if (mods & MOD_BIT(KC_LSFT)) { f(KC_LSFT); }
  if (mods & MOD_BIT(KC_RSFT)) { f(KC_RSFT); }
  if (mods & MOD_BIT(KC_RALT)) { f(KC_RALT); }
  if (mods & MOD_BIT(KC_RCTL)) { f(KC_RCTL); }
  if (mods & MOD_BIT(KC_RGUI)) { f(KC_RGUI); }
}

// taps a key (press and release)
void tap_key(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
}

void matrix_init_user(void) {
    clear_event();
}
