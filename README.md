# dactyl-manuform
This repo contains my custom key mapping and custom firmware for my 4x6 
dactyl-manuform.
<br> 
## Custom Key Mapping
The key mapping is Colemak-DHm with a layer for Vim navigation

## Custom Firmware
### Home Row Modifiers
Colemak-DHm has an "L" shaped home row:
```
A R S T     N E I O 
      D     H
```
I have configured my keyboard so that some keys behave life modifiers when held
down:
    * R -> LCtrl
    * S -> LAlt
    * I -> LCtrl
    * E -> LAlt

This is super useful because I frequently use modifiers to swith tmux panes,
and windows. 

#### Problems With QMK TapDown:
Colemak-DHm has a lot of finger roll actions on the home row. <br>
If QMK's **TapDown** feature is used to implement home row modifiers, finger
rolls will often result in unwanted behavior over home row modifiers such as
typing `LCtrl o` instead of `io` because not not releasing `i` before 
typing `o`.

### Solution:
The behavior we want: 
* For a finger rolls, fire individual characters instead of firing modifiers
* The code is inspired by [THE DARNEDST THING](http://thedarnedestthing.com/rolling%20qmk%20modifiers)
* **This version activates HRMs only when a second key is pressed**

### Implementation Notes:
* At key press, if a modifier if held down for a duration shorter than the
  HOLD_THRESHOLD while a normal key is pressed, we can immediately fire the
  first key and the second key. We know this because the behavior of a normal
  key is deterministic -- a normal key always fires a character. 

* The same is not true if the second key is a home row modifier because we do
  not know if the second key if meant to be a character or a modifier.
    * In this case, we can only be sure when the key is released

* If HRM key is repeatedly pressed, the `prev_key` and `column` will be the
  same. This is harmful because even though `prev_key` was already released,
  the code will think `prev_key` is still held down because 
  `prev_key == column`, and `e[prev_key].key_timer == e[column].key_timer`.
    * The bug was fixed by adding a conditional that checks for this
     senario.


### TODO
- [ ] Currently, holding down a home row modifier key while the modifier is
    aleady activated will only register the second key once
    * for example, holding down `Ctrl e` in Vim will only register once
    * this can be fixed by making the mod_roll function return a boolean, which
      will indicate whether to use the default behavior or not.
        * for this particular example, `e` should return true when pressed so
          that it will have the default behavior, which will allow the key to
          be registered multiple times when held down

- [ ] because I used a hacky way to disable default behavior for non-HRM keys 
    when LCtrl is activated by HRM, using my layer toggle key does not work any
    more when LCtrl was activated using HRM.

- [x] The code right now will remove all the modifiers when it detects a finger
    roll. This behavior is not alway desirable such as in the following case:
    * a finger roll involving a modifier key while `LCtrl` is held down. 
    * this will remove the effect of `LCtrl`
        * this behavior can be suppressed by keeping track of which actual
          modifier keys are held down.

