// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
enum custom_keycodes
{
    DRAG_SCROLL = SAFE_RANGE,
};

bool set_scrolling = false;

    /*
     * ┌───┐ ┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│ │F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘ └───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ 
     * │ ~ │ 1 │ 2 │ 3 │ 4 │ 5 │   │   │ 6 │ 7 │ 8 │ 9 │ 0 │del│ 
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤ 
     * │tab│ Q │ W │ E │ R │ T │   │   │ Y │ U │ I │ O │ P │bsp│ 
     * ├───┼───┼───┼───┼───┼───┤   │   ├───┼───┼───┼───┼───┼───┤ 
     * │ctl│ A │ S │ D │ F │ G ├───┼───┤ H │ J │ K │ L │ ; │ret│ 
     * ├───┼───┼───┼───┼───┼───┤   │   ├───┼───┼───┼───┼───┼───┤ ┌───┬───┬───┐
     * │shf│ Z │ X │ C │ V │ B │   │   │ N │ M │ , │ . │ / │sft│ │   │   │   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤ ├───┼───┼───┤
     * │cap│   │alt│spc│spc│spc│spc│spc│spc│spc│spc│alt│   │ctl│ │   │   │   │
     * └───┘   └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘   └───┘ └───┴───┴───┘
     */



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,    
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,    
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,                             
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,    XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LCTL,          KC_LALT, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT,          KC_RCTL,    XXXXXXX, XXXXXXX, XXXXXXX
    )
};


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report)
{
    if (set_scrolling)
    {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (keycode == DRAG_SCROLL && record->event.pressed)
    {
        set_scrolling = !set_scrolling;
    }
    return true;
}