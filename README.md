# dactyl-manuform
This repo contains my custom key mapping and custom firmware for my 4x6
dactyl-manuform.

## Custom Key Mapping
The key mapping is Colemak-DHm (`4x6/keymaps/custom/colemak_dhm_v3.json`).

## Custom Firmware
This version uses the generic MOD_TAP functionality provided by QMK for the
home row mods (HRMs). The tap-hold tuning lives in `4x6/config.h` and `4x6/4x6.c`:

* **Rolls stay taps.** A HRM only becomes a modifier when held past the
  `TAPPING_TERM` (200ms), or when another key is pressed *and released* while
  it is held (permissive hold, HRMs only).
* **Quick modifiers.** To activate the modifier without waiting for the
  `TAPPING_TERM`, hold the HRM and tap the other key. This works on either
  hand, e.g. `Ctrl+W` and `Ctrl+L`.
* **H/E pair.** Chordal hold is limited to H and E: while one is held, pressing
  the other always types both letters, so "he"/"eh" rolls never fire GUI/Shift.
* **No quick-tap repeat.** `QUICK_TAP_TERM 0`, so tapping a HRM and then holding
  it right away gives the modifier, not a repeated letter.
* **Thumb keys.** Left `LT(1, Enter)` (100ms) and left `LT(3, Space)` switch
  layers as soon as another key is pressed. Right `LT(2, Space)` is the "safe"
  space: no permissive hold, so rolls always type a space.

## Flashing The Keyboard
The QMK WSL distro builds from `qmk_firmware/keyboards/handwired/dactyl_manuform/4x6`,
which is a symlink to the `4x6` folder of a clone of this repo. After pushing
changes, `git pull` in that clone, then from the `4x6` folder:

* elite-c: `qmk flash keymaps/custom/colemak_dhm_v3.json -bl dfu`
* pro-micro: `qmk flash keymaps/custom/colemak_dhm_v3.json`

Press the reset button once the command is waiting for the bootloader. If a change
does not seem to take effect, run `qmk clean` first.
