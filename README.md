# dactyl-manuform
This repo contains my custom key mapping and custom firmware for my 4x6 
dactyl-manuform.
<br> 
## Custom Key Mapping
The key mapping is Colemak-DHm with a layer for Vim navigation

## Custom Firmware
This version uses the geric MOD_TAP functionality provided by QMK. <br>
This is working well so far, and my custom macros in the other branches may not
be necessary. <br>

This version use the `IGNORE_MOD_TAP_INTERRUPT` macro so that finger rolls will
not trigger the MOD_TAP modifiers. <br>
 
 To quickly activate the modifier without waiting for the `TAPPING_TERM`, I can
 hold the HRM and tap the other key. This will apply the modifier to the second
 key.


## Flashing The Keyboard
### Using the json keymaps
Custom configs may not be honored for json keymaps
* elite-c: `qmk flash keymaps/custom/default.json -bl dfu`
* pro-micro: `qmk flash keymaps/custom/default.json`

## Using custom keymaps
might need `sudo apt install avrdude`
Custom configs are honored
* elite-c: `qmk flash -kb handwired/dactyl_manuform/4x6 -km custom -bl dfu`
* pro-micro: `qmk flash -kb handwired/dactyl_manuform/4x6 -km custom`

