#include QMK_KEYBOARD_H

// System States
enum app_states {
    STATE_MENU,
    STATE_TIMER,
    STATE_GAME,
    STATE_DATE,
    STATE_EDIT_TIME,
    STATE_EDIT_DATE
};
static uint8_t current_state = STATE_MENU;

// Menu Options
enum menu_options {
    MENU_TIMER,
    MENU_GAME,
    MENU_DATE,
    MENU_TOTAL
};
static uint8_t menu_cursor = MENU_TIMER;

// Variables
static bool is_character_awake = false;
static bool timer_running = false;
static uint32_t timer_start_time = 0;
static int16_t game_player_x = 10;

// Time and Date values for adjustment
static int16_t current_hour = 12;
static int16_t current_minute = 0;
static int16_t current_year = 2026;
static int16_t current_month = 7;
static int16_t current_day = 5;

// Double Click Detection Variables
static uint32_t last_click_time = 0;
#define DOUBLE_CLICK_INTERVAL 300 // Milliseconds

// Keymap layout for QMK mapping
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO
    )
};

// Monitor your 5 Switches + 1 Encoder Press
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Switch 1 (D3) - Wake up character
        if (record->event.key.row == 0 && record->event.key.col == 0) {
            is_character_awake = true;
        }
        // Switch 2 (D2) - Timer Start/Stop
        else if (record->event.key.row == 0 && record->event.key.col == 1) {
            current_state = STATE_TIMER;
            timer_running = !timer_running;
            if (timer_running) timer_start_time = timer_read32();
        }
        // Switch 3 (D1) - Left Move (Game) / Up (Menu)
        else if (record->event.key.row == 0 && record->event.key.col == 2) {
            if (current_state == STATE_GAME && game_player_x > 0) {
                game_player_x--;
            } else if (current_state == STATE_MENU) {
                menu_cursor = (menu_cursor - 1 + MENU_TOTAL) % MENU_TOTAL;
            }
        }
        // Switch 4 (D0) - Right Move (Game) / Down (Menu)
        else if (record->event.key.row == 0 && record->event.key.col == 3) {
            if (current_state == STATE_GAME && game_player_x < 20) {
                game_player_x++;
            } else if (current_state == STATE_MENU) {
                menu_cursor = (menu_cursor + 1) % MENU_TOTAL;
            }
        }
        // Switch 5 (D6) - Settings Menu Switch
        else if (record->event.key.row == 0 && record->event.key.col == 4) {
            current_state = STATE_MENU;
        }
        // Encoder Shaft Press (D7) - Confirm & Double Click Detection
        else if (record->event.key.row == 0 && record->event.key.col == 5) {
            uint32_t now = timer_read32();
            if ((now - last_click_time) < DOUBLE_CLICK_INTERVAL) {
                // Double Click Detected on Encoder Press!
                if (current_state == STATE_TIMER) {
                    current_state = STATE_EDIT_TIME; // Edit Time
                } else if (current_state == STATE_DATE) {
                    current_state = STATE_EDIT_DATE; // Edit Date
                }
            } else {
                // Single Click on Encoder Press
                if (current_state == STATE_MENU) {
                    if (menu_cursor == MENU_TIMER) current_state = STATE_TIMER;
                    else if (menu_cursor == MENU_GAME) current_state = STATE_GAME;
                    else if (menu_cursor == MENU_DATE) current_state = STATE_DATE;
                } else if (current_state == STATE_EDIT_TIME) {
                    current_state = STATE_TIMER; // Save Time
                } else if (current_state == STATE_EDIT_DATE) {
                    current_state = STATE_DATE;  // Save Date
                }
            }
            last_click_time = now;
        }
    } else {
        if (record->event.key.row == 0 && record->event.key.col == 0) {
            is_character_awake = false;
        }
    }
    return true;
}

// OLED Display Output
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_character_awake) {
        oled_write_P(PSTR("  (*_*) Wake Up!\n  Xavier is here!\n"), false);
        return false;
    }

    char display_str[32];
    switch (current_state) {
        case STATE_MENU:
            oled_write_P(PSTR("--- MAIN MENU ---\n"), false);
            oled_write_P(menu_cursor == MENU_TIMER ? PSTR("> 1. Time / Timer\n") : PSTR("  1. Time / Timer\n"), false);
            oled_write_P(menu_cursor == MENU_GAME  ? PSTR("> 2. Mini Game\n") : PSTR("  2. Mini Game\n"), false);
            oled_write_P(menu_cursor == MENU_DATE  ? PSTR("> 3. Date Mode\n") : PSTR("  3. Date Mode\n"), false);
            break;

        case STATE_TIMER:
            oled_write_P(PSTR("--- TIME / TIMER ---\n"), false);
            snprintf(display_str, sizeof(display_str), "Clock: %02d:%02d\n", current_hour, current_minute);
            oled_write(display_str, false);
            oled_write_P(PSTR("[Double Click] Edit\n"), false);
            break;

        case STATE_EDIT_TIME:
            oled_write_P(PSTR("--- EDIT TIME ---\n"), false);
            snprintf(display_str, sizeof(display_str), "Adjust: %02d:%02d\n", current_hour, current_minute);
            oled_write(display_str, false);
            oled_write_P(PSTR("Turn Knob to change\n[Click] to Save\n"), false);
            break;

        case STATE_GAME:
            oled_write_P(PSTR("--- MINI GAME ---\n"), false);
            snprintf(display_str, sizeof(display_str), "Player Pos: %d\n", game_player_x);
            oled_write(display_str, false);
            oled_write_P(PSTR("[SW3]<-  ->[SW4]\n"), false);
            break;

        case STATE_DATE:
            oled_write_P(PSTR("--- DATE MODE ---\n"), false);
            snprintf(display_str, sizeof(display_str), "Date: %04d/%02d/%02d\n", current_year, current_month, current_day);
            oled_write(display_str, false);
            oled_write_P(PSTR("[Double Click] Edit\n"), false);
            break;

        case STATE_EDIT_DATE:
            oled_write_P(PSTR("--- EDIT DATE ---\n"), false);
            snprintf(display_str, sizeof(display_str), "Adjust: %04d/%02d/%02d\n", current_year, current_month, current_day);
            oled_write(display_str, false);
            oled_write_P(PSTR("Turn Knob to change\n[Click] to Save\n"), false);
            break;
    }
    return false;
}
#endif

// Encoder Adjustment Logic (Turning Knob)
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (current_state == STATE_EDIT_TIME) {
            if (clockwise) {
                current_minute = (current_minute + 1) % 60;
            } else {
                current_minute = (current_minute - 1 + 60) % 60;
            }
        } else if (current_state == STATE_EDIT_DATE) {
            if (clockwise) {
                current_day = (current_day % 31) + 1;
            } else {
                current_day = (current_day - 2 + 31) % 31 + 1;
            }
        }
    }
    return true;
}
#endif
