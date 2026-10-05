/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// USB IDs, matrix pins and diode direction live in keyboard.json

// left LT(1, KC_ENT) and LT(3, KC_SPC) switch layers as soon as another key is
// pressed; every other tap-hold key lets rolls type both keys. details in 4x6.c
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// disable tap-then-hold auto-repeat so a quick re-press of a HRM can still
// become a hold (e.g. s, then hold s + / => "s?" instead of "ss/")
#define QUICK_TAP_TERM 0

// HRMs fire immediately when another key is tapped while held. CHORDAL_HOLD is
// only used to block the H/E pair. Thumb layer-taps are excluded so the right
// space stays safe. details in 4x6.c
#define PERMISSIVE_HOLD_PER_KEY
#define CHORDAL_HOLD

#define ONESHOT_TIMEOUT 500

