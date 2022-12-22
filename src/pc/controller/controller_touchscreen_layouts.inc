//Not gonna name it .inc.c because of makefile.
//This file will have more layouts for dynamic controls later.

#include "pc/djui/djui_panel.h"

#define HIDE_POS -1000

//DEFAULT
struct Position GetDefaultJoystickPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(60) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 720 };
    return ret;
}

struct Position GetDefaultStartPos() {
    struct Position ret = { .x = SCREEN_WIDTH_API / 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 900 };
    return ret;
}

struct Position GetDefaultAPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(20) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 600 };
    return ret;
}

struct Position GetDefaultBPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(50) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 600 };
    return ret;
}

struct Position GetDefaultZPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(20) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 720 };
    return ret;
}

struct Position GetDefaultLPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(20) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 170 };
    return ret;
}

struct Position GetDefaultRPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(50) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 170 };
    return ret;
}

struct Position GetDefaultUpPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(50) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 170 };
    return ret;
}

struct Position GetDefaultDownPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(50) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 410 };
    return ret;
}

struct Position GetDefaultLeftPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(80) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 290 };
    return ret;
}

struct Position GetDefaultRightPos() {
    struct Position ret = { .x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(20) << 2, 
                            .y = djui_panel_is_active() ? HIDE_POS : 290 };
    return ret;
}

static struct ControlElement ControlElementsDefault[] = {
{.type = Joystick, .GetPos = GetDefaultJoystickPos},
{.type = Button, .GetPos = GetDefaultStartPos, .character = 's', .buttonID = START_BUTTON},
{.type = Button, .GetPos = GetDefaultAPos, .character = 'a', .buttonID = A_BUTTON},
{.type = Button, .GetPos = GetDefaultBPos, .character = 'b', .buttonID = B_BUTTON},
{.type = Button, .GetPos = GetDefaultZPos, .character = 'z', .buttonID = Z_TRIG},
{.type = Button, .GetPos = GetDefaultLPos, .character = 'l', .buttonID = L_TRIG},
{.type = Button, .GetPos = GetDefaultRPos, .character = 'r', .buttonID = R_TRIG},
{.type = Button, .GetPos = GetDefaultUpPos, .character = 'u', .buttonID = U_CBUTTONS},
{.type = Button, .GetPos = GetDefaultDownPos, .character = 'd', .buttonID = D_CBUTTONS},
{.type = Button, .GetPos = GetDefaultLeftPos, .character = 'l', .buttonID = L_CBUTTONS},
{.type = Button, .GetPos = GetDefaultRightPos, .character = 'r', .buttonID = R_CBUTTONS}
};
