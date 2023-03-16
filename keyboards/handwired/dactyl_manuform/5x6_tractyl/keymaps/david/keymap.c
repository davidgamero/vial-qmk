#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
};

//Tap dance enums
enum {
  E_ESC = 0,
  M_BSPC = 1,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2        , KC_3        , KC_4        , KC_5  ,                         KC_6  , KC_7        , KC_8        , KC_9        , KC_0   ,KC_BSPC  ,
        KC_TAB , KC_Q  , KC_W        , TD(E_ESC)   , KC_R        , KC_T  ,                         KC_Y  , KC_U        , KC_I        , KC_O        , KC_P   ,KC_MINS  ,
        KC_LSFT, KC_A  , LALT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G  ,                         KC_H  , LGUI_T(KC_J),LCTL_T(KC_K) ,LALT_T(KC_L) ,KC_SCLN ,KC_QUOT  ,
        KC_LCTL, KC_Z  , KC_X        , KC_C        , KC_V        , KC_B  ,                         KC_N  , TD(M_BSPC)        ,KC_COMM      ,KC_DOT       ,KC_SLSH ,KC_BSLASH,
                         KC_LBRC,KC_RBRC,                                                            TO(_RAISE), KC_PLUS, KC_EQL,
                                           RAISE,LSFT_T(KC_SPC),                               LSFT_T(KC_SPC),
                                               KC_TAB,KC_HOME,                        LOWER,  KC_BTN1,
                                               KC_BSPC, KC_GRV
    ),

    [_LOWER] = LAYOUT_5x6(
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                                                _______,KC_PSCR,                          _______,_______, KC_P0,
                                                _______,_______,                          _______,
                                                _______,_______,            _______,_______,
                                                _______,_______

    ),

    [_RAISE] = LAYOUT_5x6(
          KC_F12 ,  KC_F1  , KC_F2   , KC_F3   , KC_F4   ,  KC_F5   ,                       KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______, _______ , KC_AT   , KC_LCBR , KC_RCBR , _______  ,                       KC_RBRC,_______,LCTL(KC_TAB),LCMD(KC_TAB),KC_SLCK,KC_MUTE,
          KC_TAB , KC_TAB  , KC_EQL  , KC_LBRC , KC_RBRC , KC_GRAVE ,                       KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,KC_ENT,KC_VOLU,
          _______, _______ , KC_UNDS , KC_LPRN , KC_RPRN , _______  ,                       _______,KC_BSPC,_______,_______,_______,KC_VOLD,
                            _______  , _______ ,                                                    _______,_______,_______,
                                       _______ , TO(_QWERTY),                                  _______,
                                                 _______ , _______ ,               _______,_______,
                                                 _______ , _______
    )
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else return 8;
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_E); break;
    case SINGLE_HOLD: register_code(KC_ESC); break;
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_E); break;
    case SINGLE_HOLD: unregister_code(KC_ESC); break;
  }
  xtap_state.state = 0;
}

static tap m_tap_state = {
  .is_press_action = true,
  .state = 0
};
void m_finished (qk_tap_dance_state_t *state, void *user_data) {
  m_tap_state.state = cur_dance(state);
  switch (m_tap_state.state) {
    case SINGLE_TAP: register_code(KC_M); break;
    case SINGLE_HOLD: register_code(KC_BSPC); break;
  }
}

void m_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (m_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_M); break;
    case SINGLE_HOLD: unregister_code(KC_BSPC); break;
  }
  m_tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [E_ESC]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset),
  [M_BSPC]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL,m_finished, m_reset)
};
