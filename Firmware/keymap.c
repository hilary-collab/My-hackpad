#include QMK_KEYBOARD_H

// 1. 對接 1x6 直連虛擬矩陣 (外觀排版採用你想要的 2x3 實體視覺排列)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
        { KC_A, KC_B, KC_MUTE, KC_C, KC_D, KC_E }
    }
};

// 2. 狀態機與選單變數定義
enum app_states {
    STATE_MENU,
    STATE_TIMER,
    STATE_GAME,
    STATE_EDIT_TIME,
    STATE_DATE,
    STATE_EDIT_DATE
};

static uint8_t current_state = STATE_MENU;

enum menu_options {
    MENU_TIMER,
    MENU_GAME,
    MENU_DATE,
    MENU_TOTAL
};

static uint8_t menu_cursor = MENU_TIMER;

// 3. 處理按鍵行為的核心狀態邏輯
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        
        // --- 情況 1：如果你目前處於「主選單 (STATE_MENU)」---
        if (current_state == STATE_MENU) {
            // 假設我們把「第 5 粒掣 (KC_E)」定義為【確認進入】
            if (keycode == KC_E) { 
                if (menu_cursor == MENU_TIMER) {
                    current_state = STATE_TIMER;
                } else if (menu_cursor == MENU_GAME) {
                    current_state = STATE_GAME;
                } else if (menu_cursor == MENU_DATE) {
                    current_state = STATE_DATE;
                }
                return false; // 阻截原本的 KC_E 鍵位，唔好發射 "E" 字去電腦
            }
        }
        
        // --- 情況 2：如果你處於「計時器 (STATE_TIMER)」---
        else if (current_state == STATE_TIMER) {
            // 在此編寫計時器模式下，按鍵分別做咩 (例如：撳 KC_A 等於開始/暫停)
            
            // 記得要設一粒掣可以【返回主選單】。注意：你的旋鈕按壓引腳對應的是 KC_MUTE
            if (keycode == KC_MUTE) { 
                current_state = STATE_MENU; 
                return false; 
            }
        }
        
        // --- 情況 3：如果你處於「遊戲 (STATE_GAME)」---
        else if (current_state == STATE_GAME) {
            // 在此編寫遊戲模式下，按鍵分別做咩 (例如：KC_A, KC_B, KC_C 變成左、下、受)
            
            // 按下旋鈕按壓（KC_MUTE）返回主選單
            if (keycode == KC_MUTE) { 
                current_state = STATE_MENU; 
                return false; 
            }
        }
    }
    return true;
}

// 4. 專門處理旋鈕「左扭右扭」的功能 (例如：在主選單時用來移動游標，在其他模式用來調音量)
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // 第一組旋鈕
        if (current_state == STATE_MENU) {
            // 如果在主選單，扭動旋鈕可以用來上下移動游標
            if (clockwise) {
                menu_cursor = (menu_cursor + 1) % MENU_TOTAL;
            } else {
                menu_cursor = (menu_cursor - 1 + MENU_TOTAL) % MENU_TOTAL;
            }
        } else {
            // 如果在其他模式，扭動旋鈕回復成預設的調音量功能
            if (clockwise) {
                tap_code(KC_VOLU); // 右扭：提高音量
            } else {
                tap_code(KC_VOLD); // 左扭：降低音量
            }
        }
    }
    return false;
}
#endif // 💡 完美補齊：關閉旋鈕功能區塊，確保下方 OLED 功能能被獨立編譯！

// 5. OLED 螢幕動態繪製邏輯
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (current_state == STATE_MENU) {
        oled_write_ln_P(PSTR("--- MENU ---"), false);
        
        // 渲染選單選項與游標
        oled_write_P(PSTR(" TIMER"), (menu_cursor == MENU_TIMER));
        oled_write_ln_P(PSTR(""), false);
        
        oled_write_P(PSTR(" GAME"), (menu_cursor == MENU_GAME));
        oled_write_ln_P(PSTR(""), false);
        
        oled_write_P(PSTR(" DATE"), (menu_cursor == MENU_DATE));
        oled_write_ln_P(PSTR(""), false);
        
    } else if (current_state == STATE_TIMER) {
        oled_write_ln_P(PSTR("=== TIMER MODE ==="), false);
        oled_write_ln_P(PSTR("Press Encoder to Back"), false);
        
    } else if (current_state == STATE_GAME) {
        oled_write_ln_P(PSTR("=== GAME MODE ==="), false);
        oled_write_ln_P(PSTR("Playing..."), false);
        oled_write_ln_P(PSTR("Press Encoder to Back"), false);
    }
    return false;
}
#endif
