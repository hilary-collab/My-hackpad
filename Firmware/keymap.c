#include QMK_KEYBOARD_H
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_MUTE,    // 第一行實體按鍵 (分別對應引腳 D3, D2, D1)
        KC_C, KC_D, KC_E  // 第二行實體按鍵 (分別對應引腳 D0, D6, D7)
    )
};
// 2. 狀態機定義 (已修正：將變數中間的空格改成下底線)
enum app_states {
    STATE_MENU,
    STATE_TIMER,
    STATE_GAME,
    STATE_EDIT_TIME, // 已修正空格
    STATE_DATE,
    STATE_EDIT_DATE  // 已修正空格
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
            // 在此編寫遊戲模式下，按鍵分別做咩 (例如：KC_A, KC_B, KC_C 變成左、下、右)
            
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
#endif
