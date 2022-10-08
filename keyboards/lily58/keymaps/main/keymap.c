 /* Copyright 2017 F_YUUCHI
  * Copyright 2020 Drashna Jaelre <@drashna>
  * Copyright 2020 Ben Roesner (keycapsss.com)
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include "animation.c"


extern uint8_t is_master;

enum layers {
    _main,
    _symbols,
    _nav,
    _RGB,
    _GAME,
    _ANIME,
};

#define NAV MO(_nav)
#define SYM MO(_symbols)
#define RGB MO(_RGB)
#define GAME TG(_GAME)
#define ANIME TG(_ANIME)

uint16_t sakura_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* MAIN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | MODE |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |rainbo|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  /?  |ENTER |
 * |------+------+------+------+------+------|RGB ON |    | PLAY  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   ;  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |space | /  SYM  /       \ NAV  \  |BackSP|delite|        |
 *                   |      |      |      |/       /         \      \ |      |      |        |
 *                   `----------------------------'           '------''----------------------'
 */

 [_main] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,      KC_8,    KC_9,       KC_0,      RGB_MOD,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,      KC_I,    KC_O,       KC_P,      RGB_M_R,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,      KC_K,    KC_L,     KC_SLASH,    KC_ENTER,
  KC_LCTRL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    RGB_TOG,       KC_MEDIA_PLAY_PAUSE,  KC_N,    KC_M,    KC_COMMA, KC_DOT,  KC_SEMICOLON,  KC_COLN,
                            KC_LALT, KC_LGUI, KC_SPACE,   SYM,                NAV,        KC_BSPC,  KC_DELETE, _______
),




/* SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |CON f4|ALT f4|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |   [  |   ]  |      |                    |   |  |  &   |   +  |   {  |  }   |   `  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   =  |   -  |   (  |   )  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   _  |   ~  |   '  |   "  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_symbols] = LAYOUT(
  _______, _______, _______, _______, C(KC_F4), A(KC_F4),                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_LBRC, KC_RBRC, _______,                       KC_PIPE, KC_AMPR, KC_PLUS, KC_LCBR, KC_RCBR, KC_GRV,
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                       KC_CIRC, KC_EQL,  KC_MINS, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______,  _______,    _______, _______, KC_ASTR, KC_UNDS, KC_TILD, KC_QUOT, KC_DQT,
                             _______, _______, _______,  _______,    _______, _______, _______, _______
),




/* NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      | prev | next |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |prt sc| home |  Up  |  F22 |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  | F10  | F11  |-------.    ,-------|  end | Left | Down | Right|peg do|      |
 * |------+------+------+------+------+------|       |    |  GAME |------+------+------+------+------+------|
 * |      | F12  |      |      |      |      |-------|    |-------|      |      |      |      |peg up|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

  [_nav] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,                            _______,     _______, KC_MEDIA_PREV_TRACK,  KC_MEDIA_NEXT_TRACK, _______, _______,
   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                         KC_PRINT_SCREEN, KC_F24,   KC_UP,  KC_F22,       _______,            _______,
  _______,   KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,                             KC_F23,     KC_LEFT,  KC_DOWN, KC_RGHT,   C(KC_PAGE_DOWN),        _______,
  _______,   KC_F12,   _______,  _______,  _______,  _______,  ANIME,      GAME,      _______,      _______, KC_HOME,  KC_END,    C(KC_PAGE_UP),         _______,
                                 _______,  _______,  _______,  _______,     _______,    _______,      _______, _______
), 




 /* gameing pad
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  esc |      |   1  |   2  |   3  |   4  |                    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB |   T  |   Q  |   W  |   E  |   R  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |shift |      |   A  |   S  |   D  |   F  |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   G   |    |  GAME |------+------+------+------+------+------|
 * | cont |      |      |      |   V  |   B  |-------|    |-------|      |   M  |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |   X  | space| /   C   /       \   Y  \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_GAME] = LAYOUT(
  KC_ESC,   XXXXXXX,    KC_1,    KC_2,     KC_3,    KC_4,                                   KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
  KC_TAB,    KC_T,      KC_Q,    KC_W,     KC_E,    KC_R,                                   KC_F7,    KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  KC_LSFT,  XXXXXXX,    KC_A,    KC_S,     KC_D,    KC_F,                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_LCTRL, XXXXXXX,   XXXXXXX,  XXXXXXX,  KC_V,    KC_B,    KC_G,             GAME,        XXXXXXX,   KC_M,  XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
                            KC_LALT, KC_LGUI, KC_SPACE,     KC_C,                KC_Y,   XXXXXXX,  XXXXXXX, XXXXXXX
),

//   [_GAME] = LAYOUT(
//   KC_ESC,  XXXXXXX,  KC_1,   KC_2,      KC_3,     KC_4,                  KC_F1,   KC_F2,  KC_F3,  KC_F4,   KC_F5,   KC_F6,
//   KC_TAB,   KC_T,    KC_Q,   KC_W,      KC_E,     KC_R,                  KC_F7,   KC_F8,  KC_F9,  KC_F10,  KC_F11,  KC_F12,
//   KC_LSFT, XXXXXXX,  KC_A,   KC_S,      KC_D,     KC_F,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//   KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX,   KC_V,     KC_B,  KC_G,     GAME, XXXXXXX,  KC_M,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//                       XXXXXXX,  KC_X,     KC_SPC,     KC_C,         KC_Y, XXXXXXX, XXXXXXX, XXXXXXX
//   ),




/* RGB
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |rainbo|twinkl|                    |      |RGB ON| HUE+ | SAT+ | VAL+ |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |shift |      |static|      |      |      |-------.    ,-------|      | MODE | HUE- | SAT- | VAL- |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_RGB] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_R, RGB_M_TW,                   XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,
  _______, XXXXXXX, RGB_M_P , XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX
  ),


  /* ANIME
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |  -5s | play |  +5s |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      | -10s | play | +10s |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ANIME] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX,                  XXXXXXX, KC_LEFT, KC_SPACE, KC_RGHT, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ANIME, XXXXXXX,   XXXXXXX, KC_J,      KC_K,    KC_L,   XXXXXXX, XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )

};

//orientates oleds
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}


//encoder conde 
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Second encoder */
        if (clockwise) {
            //page down
            tap_code(KC_PGDN);
        } else {
            //page up
            tap_code(KC_PGUP);
        }
    }
    else if (index == 1) { /* First encoder */
        if (clockwise) {
            //voly up
            tap_code_delay(KC_VOLU, 10);
        } else {
            //volyme down
            tap_code_delay(KC_VOLD, 10);
        }
    } 
    return false;
}




//tree redering/animation loop
// uint8_t frame = 0;
// void render_sakura(void){
//     uint16_t timer = timer_elapsed(sakura_timer); 

//     if (timer < 500)
//     {
//         oled_write_raw_P(sakura[frame], 512);
//     }
//     if (timer > 500)
//     {
//         frame++;
//         sakura_timer = timer_read();
//     }

//     if (frame > 5){ frame = 0; }
    
//     return;
// };

//sets key state for cat animation
bool isPressed = false;
void draw_cat(void) {
    if (isPressed)
    {
        oled_write_raw_P(cat[1], 512);
    }
    else{
        oled_write_raw_P(cat[0], 512);
    }
    
};

//oled render
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        //left side
        switch (get_highest_layer(layer_state)) {
            //render cat if on main layer 
        case _main:
            draw_cat();
        break;
        case _GAME:
            //render valorant logo is game layer 
            oled_write_raw_P(valorant[0], 512);
        break;
        // case _RGB:
        //     //render if rgn settings layer
        //     oled_write_raw_P(valorant[0], 512);
        // break;
    }
    } else {
        //right side  
        //run tree animation
        // render_sakura();
        oled_write_raw_P(sakura[0], 512);
    }
    return false;
};

//checks keypress
bool process_record_user(uint16_t keycode, keyrecord_t * record) {
    if (record->event.pressed) {
        isPressed = true;
    }
    else{
        isPressed = false;
    }
    return true;
};
