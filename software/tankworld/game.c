
#include "game.h"
#include <stdio.h>

// SCREEN PROPERTY
#define SCREEN_WIDTH_PIXEL              640
#define SCREEN_HEIGHT_PIXEL             480
#define COMMON_UNIT                     32 // most items are 32 * 32

// GAME
#define SET_GAME_ATTR_START(x)          (x)
#define REGENERATE_RADIUS               60
// MAP_NUM: 1: wait to choose 2: U 4: I 8: C 
#define SET_GAME_ATTR_MAP_NUM(x)        (x<<1)
#define SET_GAME_ATTR_HEALTH(x)         (x<<5)
#define SET_GAME_ATTR_SETTING(x)        (x<<10)
#define MAX_HEALTH_DEFAULT          5

// WALL
#define WALL_NUM                    16
#define WALL_LEN                    32 // WIDTH = HEIGHT = 32
#define GET_WALL_POS(x,y)           (1 | (x<<1) | (y<<11))
#define GET_WALL_X(pos)             ((pos>>1) & 0x3FF)  
#define GET_WALL_Y(pos)             ((pos>>11) & 0x3FF)

// MAP_NUM
#define UMAP                        1
#define IMAP                        2
#define CMAP                        4


// TANK
#define TANK_NUM                    2
#define GET_POS(x,y)                (x | (y<<10))
#define TANK_1_DEAULT_X             200
#define TANK_1_DEAULT_Y             200
#define TANK_2_DEAULT_X             400
#define TANK_2_DEAULT_Y             400

// COIN
#define COIN_TYPES                  3
#define GET_POS_COIN(x,y)           (1 | (x<<1) | (y<<11))
// & 3ff is to extract the last 10 bits
#define GET_COIN_X(pos)             ((pos>>1) & 0x3FF)
#define GET_COIN_Y(pos)             ((pos>>11) & 0x3FF)
#define COIN_EXIST(x)               (x & 1)

#define GOLD_COIN                   0
#define SILVER_COIN                 1
#define BRONZE_COIN                 2

#define GOLD_COIN_VAL               30
#define SILVER_COIN_VAL             20
#define BRONZE_COIN_VAL             10

#define GOLD_COIN_DEFAULT_X         320
#define GOLD_COIN_DEFAULT_Y         240

#define SILVER_COIN_DEFAULT_X       320
#define SILVER_COIN_DEFAULT_Y       100

#define BRONZE_COIN_DEFAULT_X       320
#define BRONZE_COIN_DEFAULT_Y       380

// GEAR
#define GEAR_TYPES                  2
#define GET_POS_GEAR(x,y)           (1 | (x<<1) | (y<<11))
#define GET_GEAR_X(pos)             ((pos>>1) & 0x3FF)
#define GET_GEAR_Y(pos)             ((pos>>11) & 0x3FF)
#define GEAR_EXIST(x)               (x & 1)

// -16 is because it's more intuitive to specify the center then we find the top left corner of the gear

#define HEALTH_GEAR_DEAFULT_X       (320 - 16)
#define HEALTH_GEAR_DEAFULT_Y       (40 - 16)

#define SPEED_GEAR_DEAFULT_X        (320 - 16)
#define SPEED_GEAR_DEAFULT_Y        (430 - 16)

// MENU
#define TEXT_SCREEN_X               80
#define TEXT_SCREEN_Y               30
#define MENU_HEIGHT                 15
#define MENU_WIDTH                  40

// MENU : line spacing
#define MENU_STARTING_ROW           4
#define MENU_UPPER_PADDING          1
#define MENU_PADDING_1              3

#define MENU_LEFT_PADDING           ((TEXT_SCREEN_X - MENU_WIDTH) >> 1)

#define MENU_START_ROW_IND          0
#define MENU_MAP_ROW_IND            1
#define MENU_SETTINGS_ROW_IND       2

// COLOR CODES
#define PADDING_COLOR               6  // cyan
#define FONT_COLOR                  3  // brown
#define HIGH_LIGHT_PADDING_COLOR    1  // blue
#define HIGH_LIGHT_FONT_COLOR       15 // white
#define WIN_COLOR                   4  // red

// STATUS BARS
#define STATUS_BAR_LEN              10

#define TANK_1_STATUS_BAR_Y         1
#define TANK_1_STATUS_BAR_X         1

#define TANK_2_STATUS_BAR_X         (TEXT_SCREEN_X - STATUS_BAR_LEN - 2)
#define TANK_2_STATUS_BAR_Y         1

// SCORE PANEL
#define SCORE_PANEL_X               ((TEXT_SCREEN_X - SCORE_PANEL_WIDTH) >> 1)
#define SCORE_PANEL_Y               5

#define SCORE_PANEL_HEIGHT          22
#define SCORE_PANEL_WIDTH           40


#define SCORE_PANEL_UPER_PADDING    4
#define SCORE_PANEL_PADDING_1       6
#define SCORE_PANEL_PADDING_2       2




static int cursor_pos = MENU_START_ROW_IND; // cursor position, 0 for start, 1 for map, 2 for settings

// check if two rectangles (32 * 32) intersect
static int _check_overlap(int x1, int y1, int x2, int y2) {
    if (x1 > x2 + COMMON_UNIT || x2 > x1 + COMMON_UNIT || y1 > y2 + COMMON_UNIT || y2 > y1 + COMMON_UNIT) 
        return 0;
    else
        return 1;
}


void game_init(void) {
    int i;
    // set the game attributes : not started, map 0, maximum health 5
    vga_ctrl->game_attr = SET_GAME_ATTR_START(0) | SET_GAME_ATTR_MAP_NUM(0) | SET_GAME_ATTR_HEALTH(MAX_HEALTH_DEFAULT);
    // mark all the coins present with default positions
    vga_ctrl->coin_attr[GOLD_COIN] = GET_POS_COIN(GOLD_COIN_DEFAULT_X, GOLD_COIN_DEFAULT_Y);
    vga_ctrl->coin_attr[SILVER_COIN] = GET_POS_COIN(SILVER_COIN_DEFAULT_X, SILVER_COIN_DEFAULT_Y);
    vga_ctrl->coin_attr[BRONZE_COIN] = GET_POS_COIN(BRONZE_COIN_DEFAULT_X, BRONZE_COIN_DEFAULT_Y);
    // health is read only
    for(i=0; i<TANK_NUM; i++) vga_ctrl->score[i] = 0;
    vga_ctrl->init_pos[0] = GET_POS(TANK_1_DEAULT_X, TANK_1_DEAULT_Y);
    vga_ctrl->init_pos[1] = GET_POS(TANK_2_DEAULT_X, TANK_2_DEAULT_Y);
    for(i = 0; i < WALL_NUM; i++) vga_ctrl->wall_pos[i] = 0;
    vga_ctrl->gear_attr[0] = GET_POS_GEAR(HEALTH_GEAR_DEAFULT_X, HEALTH_GEAR_DEAFULT_Y);
    vga_ctrl->gear_attr[1] = GET_POS_GEAR(SPEED_GEAR_DEAFULT_X, SPEED_GEAR_DEAFULT_Y);
}

/**
 * @brief We show menu by displaying equal length of string, blank should be padded with space.
 * Should not use black color as both background and foreground color.
 * textVGADrawColorText (color_string, x, y, bg, fg) will show the string with upper left corner at (x,y), 
 * with background color bg and foreground color fg. Definition of colors are in text_mode_vga.h.
 * @todo : currently only start will work, map and settings are not implemented.
 */
void show_menu(int choice, int is_map) {
    char color_string[80]; // maximum 80 characters per line, each character is 8x16 pixels
    int i, y;
    char start_back = PADDING_COLOR;
    char start_font = FONT_COLOR;
    char map_back = PADDING_COLOR;
    char map_font = FONT_COLOR;
    char setting_back = PADDING_COLOR;
    char setting_font = FONT_COLOR;
    y = MENU_STARTING_ROW;
    switch (choice)
    {
    case START:
        start_back = HIGH_LIGHT_PADDING_COLOR;
        start_font = HIGH_LIGHT_FONT_COLOR;
        break;
    case MAP:
        map_back = HIGH_LIGHT_PADDING_COLOR;
        map_font = HIGH_LIGHT_FONT_COLOR;
        break;
    case SETTING:
        setting_back = HIGH_LIGHT_PADDING_COLOR;
        setting_font = HIGH_LIGHT_FONT_COLOR;
        break;
    default:
        break;
    }
    // draw the upper padding rows
    for(i=0; i<MENU_UPPER_PADDING; i++) {
        sprintf(color_string, "                                        ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, PADDING_COLOR, PADDING_COLOR);
    }
    // draw the menu rows, center "MENU"
    sprintf(color_string, "                MENU                    ");
    textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, PADDING_COLOR, FONT_COLOR);
    // draw padding 1
    for(i=0; i<MENU_PADDING_1; i++) {
        sprintf(color_string, "                                        ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, PADDING_COLOR, PADDING_COLOR);
    }
    if (is_map == 0){
        // draw 3 menu items "START", "MAP", "SETTINGS"
        sprintf(color_string, "                START                   ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, start_back, start_font);
        sprintf(color_string, "                 MAP                    ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, map_back, map_font);
        sprintf(color_string, "              SETTINGS                  ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, setting_back, setting_font);
    }
    else{
        // draw 3 menu items "U MAP", "I MAP", "C MAP"
        sprintf(color_string, "                U MAP                   ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, start_back, start_font);
        sprintf(color_string, "                I MAP                   ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, map_back, map_font);
        sprintf(color_string, "                C MAP                   ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, setting_back, setting_font);
    }
    // draw lower padding
    for(i = 0; i < MENU_STARTING_ROW + MENU_HEIGHT - y; i++) {
        sprintf(color_string, "                                        ");
        textVGADrawColorText(color_string, MENU_LEFT_PADDING, y++, PADDING_COLOR, PADDING_COLOR);
    }
}


/**
 * @brief Status bar shows the HEALTH, SCORE, and BULLETS of the tank.
 */
void draw_status_bars(void) {
    // draw the status bar for tank 0
    char color_string[80];
    int y;
    y = TANK_1_STATUS_BAR_Y;
    // pad the string to length of STATUS_BAR_LEN
    sprintf(color_string, "HEALTH:  %01lu", vga_ctrl->health[0]);
    textVGADrawColorText(color_string, TANK_1_STATUS_BAR_X, y++, PADDING_COLOR, FONT_COLOR);
    // keep pad the score to 3 digits
    sprintf(color_string, "SCORE: %03lu", vga_ctrl->score[0]);
    textVGADrawColorText(color_string, TANK_1_STATUS_BAR_X, y++, PADDING_COLOR, FONT_COLOR);
    // keep pad the bullets to 1 digits
    sprintf(color_string, "BULLETS: %01lu", vga_ctrl->bullet_num[0]);
    textVGADrawColorText(color_string, TANK_1_STATUS_BAR_X, y++, PADDING_COLOR, FONT_COLOR);

    // do the same for tank2
    y = TANK_2_STATUS_BAR_Y;
    sprintf(color_string, "HEALTH:  %01lu", vga_ctrl->health[1]);
    textVGADrawColorText(color_string, TANK_2_STATUS_BAR_X, y++, PADDING_COLOR, FONT_COLOR);
    sprintf(color_string, "SCORE: %03lu", vga_ctrl->score[1]); 
    textVGADrawColorText(color_string, TANK_2_STATUS_BAR_X, y++, PADDING_COLOR, FONT_COLOR);
    sprintf(color_string, "BULLETS: %01lu", vga_ctrl->bullet_num[1]);
    textVGADrawColorText(color_string, TANK_2_STATUS_BAR_X, y++, PADDING_COLOR, FONT_COLOR);
}

/**
 * @brief given a wall with ( @param x , @param y ) as its top left corner, check if the wall occupy the same space as the tank, coin, and othe props
 */
#define NUM_BACK_UP_POS                 4
#define BACK_UP_POS_X_1                 100
#define BACK_UP_POS_Y_1                 150
#define BACK_UP_POS_X_2                 BACK_UP_POS_X_1
#define BACK_UP_POS_Y_2                 (BACK_UP_POS_Y_1 + WALL_LEN)
#define BACK_UP_POS_X_3                 (SCREEN_WIDTH_PIXEL - BACK_UP_POS_X_1 - WALL_LEN)
#define BACK_UP_POS_Y_3                 BACK_UP_POS_Y_1
#define BACK_UP_POS_X_4                 BACK_UP_POS_X_3
#define BACK_UP_POS_Y_4                 BACK_UP_POS_Y_2
static int __pull_back_up_walls() {
    static int i = 0;
    if(i == NUM_BACK_UP_POS) return -1;
    return i++;
}
// @return new wall position
// if wall is not legal, then we pull one legal position from back_up_positions
static int _get_real_wall_pos(int x, int y) {
    int coin_x[COIN_TYPES], coin_y[COIN_TYPES];
    int gear_x[GEAR_TYPES], gear_y[GEAR_TYPES];
    int back_up_ind;
    int i;
    // second dimenstion is (x,y)
    static back_up_positions[NUM_BACK_UP_POS][2] = {{BACK_UP_POS_X_1, BACK_UP_POS_Y_1}, {BACK_UP_POS_X_2, BACK_UP_POS_Y_2}, {BACK_UP_POS_X_3, BACK_UP_POS_Y_3}, {BACK_UP_POS_X_4, BACK_UP_POS_Y_4}};
    // check if wall and coin overlaps
     for(i = 0; i < COIN_TYPES; i++) { // very special, coin's coordinate is the center, we need to convert them to upper left
        coin_x[i] = GET_COIN_X(vga_ctrl->coin_attr[i]) - 16;
        coin_y[i] = GET_COIN_Y(vga_ctrl->coin_attr[i]) - 16;
    }
    for(i = 0; i < GEAR_TYPES; i++) {
        gear_x[i] = GET_GEAR_X(vga_ctrl->gear_attr[i]);
        gear_y[i] = GET_GEAR_Y(vga_ctrl->gear_attr[i]);
    }

    // check if wall and coin overlaps
    for(i = 0; i < COIN_TYPES; i++) {
        if(COIN_EXIST(vga_ctrl->coin_attr[i]) && _check_overlap(x, y, coin_x[i], coin_y[i])) {
            back_up_ind = __pull_back_up_walls();
            return GET_WALL_POS(back_up_positions[back_up_ind][0], back_up_positions[back_up_ind][1]);
        }
    }

    // check if wall and gear overlaps
    for(i = 0; i < GEAR_TYPES; i++) {
        if(GEAR_EXIST(vga_ctrl->gear_attr[i]) && _check_overlap(x, y, gear_x[i], gear_y[i])) {
            back_up_ind = __pull_back_up_walls();
            return GET_WALL_POS(back_up_positions[back_up_ind][0], back_up_positions[back_up_ind][1]);
        }
    }

    // if original wall position is legal, then return it, three return result are 
    // in form of (1 | (x << 1) | (y << 11)) with first bit valid bit set to 1
    return GET_WALL_POS(x, y);
}

void draw_wall(void) {
    static wall_drawn = 0;
    int map_type = (vga_ctrl->game_attr >> 1) & 0xF;
    int x_leftinitial, y_initial, x_rightinitial, y_bottom, x_bottomleft;
    int x_middle, y_up;
    if(wall_drawn) return;
    wall_drawn = 1;
    printf("map type: %d\n", map_type);
    switch (map_type){
    case 1:
        x_leftinitial = 240;
        y_initial = 144;
        x_rightinitial = 368;
        y_bottom = 304;
        x_bottomleft = 272;
        // draw left vertical line of 'U'
        for (int i = 0; i < 6; i++){
            vga_ctrl->wall_pos[i] = _get_real_wall_pos(x_leftinitial, y_initial + i * 32);
        }
        // draw right vertical line of 'U'
        for (int i = 0; i < 6; i++){
            vga_ctrl->wall_pos[i + 6] = _get_real_wall_pos(x_rightinitial, y_initial + i * 32);
        }
        // draw bottom horizontal line of 'U'
        for (int i = 0; i < 3; i++){
            vga_ctrl->wall_pos[i + 12] = _get_real_wall_pos(x_bottomleft + i * 32, y_bottom);
        }
        break;
    case 2:
        x_leftinitial = 272;
        y_initial = 112;
        y_bottom = 336;
        x_middle = 304;
        y_up = 144;
        // draw the upper horizontal line
        for (int i = 0; i < 3; i++){
            vga_ctrl->wall_pos[i] = _get_real_wall_pos(x_leftinitial + i * 32, y_initial);
        }
        // draw the lower horizontal line
        for (int i = 0; i < 3; i++){
            vga_ctrl->wall_pos[i+3] = _get_real_wall_pos(x_leftinitial + i * 32, y_bottom);
        }
        // draw the middel vertical line
        for (int i = 0; i < 6; i++){
            vga_ctrl->wall_pos[i+6] = _get_real_wall_pos(x_middle + i * 32, y_up);
        }
        break;
    case 4:
        x_middle = 272;
        y_up = 160;
        y_bottom = 288;
        x_leftinitial = 240;
        // draw the upper horizontal line
        for (int i = 0; i < 4; i++){
            vga_ctrl->wall_pos[i] = _get_real_wall_pos(x_middle + i * 32, y_up);
        }
        // draw the lower horizontal line
        for (int i = 0; i < 4; i++){
            vga_ctrl->wall_pos[i+4] = _get_real_wall_pos(x_middle + i * 32, y_bottom);
        }
        // draw the left vertical line
        for (int i = 0; i < 5; i++){
            vga_ctrl->wall_pos[i+8] = _get_real_wall_pos(x_leftinitial, y_up + i * 32);
        }
        break;
    default:
        x_leftinitial = 272;
        y_initial = 112;
        y_bottom = 336;
        x_middle = 304;
        y_up = 144;
        // draw the upper horizontal line
        for (int i = 0; i < 3; i++){
            vga_ctrl->wall_pos[i] = _get_real_wall_pos(x_leftinitial + i * 32, y_initial);
        }
        // draw the lower horizontal line
        for (int i = 0; i < 3; i++){
            vga_ctrl->wall_pos[i+3] = _get_real_wall_pos(x_leftinitial + i * 32, y_bottom);
        }
        // draw the middel vertical line
        for (int i = 0; i < 6; i++){
            vga_ctrl->wall_pos[i+6] = _get_real_wall_pos(x_middle, y_up + i * 32);
        }
        break;
    }
}

static void clear_except_score_panel(void) {
    int i, j;
    for(i = 0; i < TEXT_SCREEN_Y; i++) {
        for(j = 0; j < TEXT_SCREEN_X; j++) {
            if(j < SCORE_PANEL_X || j > SCORE_PANEL_X + SCORE_PANEL_WIDTH 
            || i < SCORE_PANEL_Y || i > SCORE_PANEL_Y + SCORE_PANEL_HEIGHT) {
                vga_ctrl->VRAM[(i * TEXT_SCREEN_X + j) * 2] = 
                vga_ctrl->VRAM[(i * TEXT_SCREEN_X + j) * 2 + 1] = 0;
            }
        }
    }
}

void draw_score_panel(void) {
    char color_string[80];
    int y;
    clear_except_score_panel();
    y = SCORE_PANEL_Y;
    if(vga_ctrl->health[0] < 50 && vga_ctrl->health[0] > 0) {// player left wins,  display "WIN  LOSE" split string into 2 length 20 string, center WIN, LOSE respectively
        sprintf(color_string, "        WIN         ");
        textVGADrawColorText(color_string, SCORE_PANEL_X, y, PADDING_COLOR, WIN_COLOR);
        sprintf(color_string, "        LOSE        ");
        textVGADrawColorText(color_string, SCORE_PANEL_X + 20, y++, PADDING_COLOR, FONT_COLOR);
    }
    else {// player right wins, display "LOSE  WIN"
        sprintf(color_string, "        LOSE        ");
        textVGADrawColorText(color_string, SCORE_PANEL_X, y, PADDING_COLOR, FONT_COLOR);
        sprintf(color_string, "        WIN         ");
        textVGADrawColorText(color_string, SCORE_PANEL_X + 20, y++, PADDING_COLOR, WIN_COLOR);
    }
    // draw padding 1
    for(int i = 0; i < SCORE_PANEL_PADDING_1; i++) {
        sprintf(color_string, "                                        ");
        textVGADrawColorText(color_string, SCORE_PANEL_X, y++, PADDING_COLOR, PADDING_COLOR);
    }
    // draw the score
    
    sprintf(color_string, "     SCORE: %03lu     ", vga_ctrl->score[0]);
    textVGADrawColorText(color_string, SCORE_PANEL_X, y, PADDING_COLOR, FONT_COLOR);
    sprintf(color_string, "     SCORE: %03lu     ", vga_ctrl->score[1]);
    textVGADrawColorText(color_string, SCORE_PANEL_X + 20, y++, PADDING_COLOR, FONT_COLOR);

    // draw padding 2
    for(int i = 0; i < SCORE_PANEL_PADDING_2; i++) {
        sprintf(color_string, "                                        ");
        textVGADrawColorText(color_string, SCORE_PANEL_X, y++, PADDING_COLOR, PADDING_COLOR);
    }

    // draw the health
    sprintf(color_string, "     HEALTH:  %01lu     ", vga_ctrl->health[0] > 50 ? 0 : vga_ctrl->health[0]);
    textVGADrawColorText(color_string, SCORE_PANEL_X, y, PADDING_COLOR, FONT_COLOR);
    sprintf(color_string, "     HEALTH:  %01lu     ", vga_ctrl->health[1] > 50 ? 0 : vga_ctrl->health[1]);
    textVGADrawColorText(color_string, SCORE_PANEL_X + 20, y++, PADDING_COLOR, FONT_COLOR);
    
    // draw padding 3
    for(int i = 0; i < SCORE_PANEL_Y + SCORE_PANEL_HEIGHT - y; i++) {
        sprintf(color_string, "                                        ");
        textVGADrawColorText(color_string, SCORE_PANEL_X, y++, PADDING_COLOR, PADDING_COLOR);
    }
}

/**
 * @brief take at most four @param key0 @param key1 @param key2 @param key3 keys and handle the menu
 * @note currently only enter will work
 * @todo add logics for map and settings
 */
void menu_control(char* key) {
    int i;
    if (key[0] == last_key)
        return ;
    else
        last_key = key[0];
    printf("menu state: %d\n", menu_state);
	printf("game attr: %x\n", vga_ctrl->game_attr);
    for(i = 0; i < 1; i++) {
        switch (menu_state){
        case 0:
            switch (key[i]) {
            case 40: // enter
                // set the game bit 1 to start the game
                // clear the VRAM
                text_VGA_init();
                // draw the draw_status_bars
                draw_status_bars();

                // game_init();
                vga_ctrl->game_attr |= SET_GAME_ATTR_START(1);
                break;
            case 81: // down
                // redraw the menu
                // show the high light on map
                // change the game status
                menu_state = 1;
                show_menu(MAP, 0);
                break;

            default:
                printf("oops, unknown key pressed for menu\n");
                break;
            }
            break;
        // wait to choose map
        case 1: 
            switch (key[i]) {
            case 40: // enter
                // flip the wait to choose bit
                show_menu(1, 1);
                menu_state = 3;
                break;
            case 81: // down
                // redraw the menu
                // show the high light on setting
                // change the game status
                show_menu(SETTING, 0);
                menu_state = 2;
                break;

            case 82: // up
                // redraw the menu
                // show the high light on start
                // change the game status
                show_menu(START, 0);
                menu_state = 0;
                break;
            default:
                printf("oops, unknown key pressed for menu\n");
                break;
            }
            break;

        case 2:
            switch (key[i]) {
            // wait to implement SETTING
            // case 40: // enter
            //     // set the game bit 1 to start the game
            //     // clear the VRAM
            //     text_VGA_init();
            //     // draw the draw_status_bars
            //     draw_status_bars();

            //     game_init();
            //     vga_ctrl->game_attr |= SET_GAME_ATTR_START(1);
            //     break;
            case 82: // up
                // redraw the menu
                // show the high light on map
                // change the game status
                show_menu(MAP, 0);
                menu_state = 1;
                break;
            default:
                printf("oops, unknown key pressed for menu\n");
                break;
            }
            break;
        case 3:
            switch (key[i]) {
            case 40: // enter
                menu_state = 1;
                // vga_ctrl->game_attr &= 0xFFE1;
                vga_ctrl->game_attr = vga_ctrl->game_attr | 2;
                show_menu(MAP, 0);
                break;
            case 81: // down
                // redraw the menu
                // show the high light on map
                // change the game status
                menu_state = 4;
                show_menu(2, 1);
                break;

            default:
                printf("oops, unknown key pressed for menu\n");
                break;
            }
            break;
        case 4:
            switch (key[i]) {
            case 40: // enter
                menu_state = 1;
                // vga_ctrl->game_attr &= 0xFFE1;
                vga_ctrl->game_attr |= 4;
                show_menu(MAP, 0);
                break;
            case 81: // down
                // redraw the menu
                // show the high light on map
                // change the game status
                menu_state = 5;
                show_menu(3, 1);
                break;
            
            case 82: // up
                // redraw the menu
                // show the high light on map
                // change the game status
                menu_state = 3;
                show_menu(1, 1);
                break;

            default:
                printf("oops, unknown key pressed for menu\n");
                break;
            }
            break;
        case 5:
            switch (key[i]) {
            case 40: // enter
                menu_state = 1;
                // vga_ctrl->game_attr &= 0xFFE1;
                vga_ctrl->game_attr |= 8;
                show_menu(MAP, 0);
                break;
            case 82: // up
                // redraw the menu
                // show the high light on map
                // change the game status
                menu_state = 4;
                show_menu(2, 1);
                break;

            default:
                printf("oops, unknown key pressed for menu\n");
                break;
            }
            break;
        default:
            printf("oops, menu state error\n");
            break;
        }
    }
}




// check if current drawing gear with has upper left point(x,y) does not overlap with coins, walls
// @note it can overlap with other gears
static int check_gear_legal_pos(alt_u32 x, alt_u32 y) {
    int coin_x[COIN_TYPES], coin_y[COIN_TYPES];
    int wall_x[WALL_NUM], wall_y[WALL_NUM];
    int i;
    if(x < 0 || x >= SCREEN_WIDTH_PIXEL || y < 0 || y >= SCREEN_HEIGHT_PIXEL) {
        return 0;
    }

    for(i = 0; i < COIN_TYPES; i++) { // very special, coin's coordinate is the center, we need to convert them to upper left
        coin_x[i] = GET_COIN_X(vga_ctrl->coin_attr[i]) - 16;
        coin_y[i] = GET_COIN_Y(vga_ctrl->coin_attr[i]) - 16;
    }
    for(i = 0; i < WALL_NUM; i++) {
        wall_x[i] = GET_WALL_X(vga_ctrl->wall_pos[i]);
        wall_y[i] = GET_WALL_Y(vga_ctrl->wall_pos[i]);
    }
    // 
    // check if overlap with coins
    for(i = 0; i < COIN_TYPES; i++) {
        if(COIN_EXIST(vga_ctrl->coin_attr[i]) && _check_overlap(x, y, coin_x[i], coin_y[i])) {
            return 0;
        }
    }

    // check if overlap with walls

    for(i = 0; i < WALL_NUM; i++) {
        if(_check_overlap(x, y, wall_x[i], wall_y[i])) {
            return 0;
        }
    }

    return 1;
} 

// @note do not use unsigned here, we have subtraction
static int calc_dis(int x1, int y1, int x2, int y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

/**
 * @brief check if any gear is not on screen, if so, we put a new gear on the screen.
 */
void check_gears(void) {
    static int last_coin_pos[COIN_TYPES][2] = {{GOLD_COIN_DEFAULT_X, GOLD_COIN_DEFAULT_Y}, {SILVER_COIN_DEFAULT_X, SILVER_COIN_DEFAULT_Y}, {BRONZE_COIN_DEFAULT_X, BRONZE_COIN_DEFAULT_Y}};
    static int last_gear_pos[GEAR_TYPES][2] = {{HEALTH_GEAR_DEAFULT_X, HEALTH_GEAR_DEAFULT_Y}, {SPEED_GEAR_DEAFULT_X, SPEED_GEAR_DEAFULT_Y}};
    int new_x, new_y;
    int i;
    for(i = 0; i < COIN_TYPES; i++) {
        new_x = rand() % SCREEN_WIDTH_PIXEL, new_y = rand() % SCREEN_HEIGHT_PIXEL;
        // align to 32 
        new_x = new_x - new_x % 32 + 16;
        new_y = new_y - new_y % 32 + 16;
        if(!COIN_EXIST(vga_ctrl->coin_attr[i])) {
            if(check_gear_legal_pos(new_x, new_y)) { // check if new position has overlap with other gears and if new position is on screen
                if(calc_dis(new_x, new_y, last_coin_pos[i][0], last_coin_pos[i][1]) < REGENERATE_RADIUS * REGENERATE_RADIUS) { // too close to last gear, not fair
                    continue;
                }
                vga_ctrl->coin_attr[i] = GET_POS_COIN(new_x, new_y);
                last_coin_pos[i][0] = new_x;
                last_coin_pos[i][1] = new_y;
            } 
            // don't wait because we don't re-generate a new position    
        }
    }

    for(i = 0; i < GEAR_TYPES; i++) {
        new_x = rand() % SCREEN_WIDTH_PIXEL, new_y = rand() % SCREEN_HEIGHT_PIXEL;
        // align to 32
        new_x = new_x - new_x % 32;
        new_y = new_y - new_y % 32;
        if(!GEAR_EXIST(vga_ctrl->gear_attr[i])) {
            if(check_gear_legal_pos(new_x, new_y)) {
                if(calc_dis(new_x, new_y, last_gear_pos[i][0], last_gear_pos[i][1]) < REGENERATE_RADIUS * REGENERATE_RADIUS) { // too close to last gear, not fair
                    continue;
                }
                vga_ctrl->gear_attr[i] = GET_POS_GEAR(new_x, new_y);
                last_gear_pos[i][0] = new_x;
                last_gear_pos[i][1] = new_y;
            } 
            // don't wait because we don't re-generate a new position    
        }
    }

}
