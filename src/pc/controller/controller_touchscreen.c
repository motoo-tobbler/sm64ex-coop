//Feel free to use it in your port too, but please keep authorship!
//Touch Controls made by: VDavid003
#ifdef TOUCH_CONTROLS
#include <ultra64.h>
#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "config.h"
#include "sm64.h"
#include "game/game_init.h"
#include "game/memory.h"
#include "game/segment2.h"
#include "gfx_dimensions.h"
#include "pc/gfx/gfx_pc.h"
#include "pc/djui/djui_panel.h"

#include "controller_api.h"
#include "controller_touchscreen.h"
#include "../configfile.h"

#define SCREEN_WIDTH_API 1280
#define SCREEN_HEIGHT_API 960

#define LEFT_EDGE ((int)floorf(SCREEN_WIDTH_API / 2 - SCREEN_HEIGHT_API / 2 * gfx_current_dimensions.aspect_ratio))
#define RIGHT_EDGE ((int)ceilf(SCREEN_WIDTH_API / 2 + SCREEN_HEIGHT_API / 2 * gfx_current_dimensions.aspect_ratio))

#define CORRECT_TOUCH_X(x) ((x * (RIGHT_EDGE - LEFT_EDGE)) + LEFT_EDGE)
#define CORRECT_TOUCH_Y(y) (y * SCREEN_HEIGHT_API)

#define TRIGGER_DETECT(size) (((pos.x + size / 2 > CORRECT_TOUCH_X(event->x)) && (pos.x - size / 2 < CORRECT_TOUCH_X(event->x))) &&\
                              ((pos.y + size / 2 > CORRECT_TOUCH_Y(event->y)) && (pos.y - size / 2 < CORRECT_TOUCH_Y(event->y))))

#define HIDE_POS -1000

#define CHAT_BUTTON 0x001C
#define PLAYERLIST_BUTTON 0x000F

// Mouselook
s16 before_x = 0;
s16 before_y = 0;
s16 touch_x = 0;
s16 touch_y = 0;
s16 touch_cam_last_x = 0;
s16 touch_cam_last_y = 0;
static u32 timer = 0;

enum ControlElementType {
    Joystick,
    Mouse,
    Button
};

struct Position {
    s32 x,y;
};

struct ControlElement {
    enum ControlElementType type;
    u8 touchID; //0 = not being touched, 1-255 = Finger being used
    //Joystick
    int joyX, joyY;
    //Button
    int buttonID;
    u8 character;
    int slideTouch;
};

// This order must match configControlElements and ConfigControlElementIndex
static struct ControlElement ControlElements[CONTROL_ELEMENT_COUNT] = {
{.type = Joystick},
{.type = Mouse},
{.type = Button, .character = 'a', .buttonID = A_BUTTON},
{.type = Button, .character = 'b', .buttonID = B_BUTTON},
{.type = Button, .character = 137, .buttonID = X_BUTTON},
{.type = Button, .character = 'y', .buttonID = Y_BUTTON},
{.type = Button, .character = 's', .buttonID = START_BUTTON},
{.type = Button, .character = 'l', .buttonID = L_TRIG},
{.type = Button, .character = 'r', .buttonID = R_TRIG},
{.type = Button, .character = 'z', .buttonID = Z_TRIG},
{.type = Button, .character = 'u', .buttonID = U_CBUTTONS},
{.type = Button, .character = 'd', .buttonID = D_CBUTTONS},
{.type = Button, .character = 'l', .buttonID = L_CBUTTONS},
{.type = Button, .character = 'r', .buttonID = R_CBUTTONS},
{.type = Button, .character = 'q', .buttonID = CHAT_BUTTON},
{.type = Button, .character = 'p', .buttonID = PLAYERLIST_BUTTON},
{.type = Button, .character = 132, .buttonID = U_JPAD},
{.type = Button, .character = 133, .buttonID = D_JPAD},
{.type = Button, .character = 134, .buttonID = L_JPAD},
{.type = Button, .character = 135, .buttonID = R_JPAD},
};

static int ControlElementsLength = sizeof(ControlElements)/sizeof(struct ControlElement);

struct Position get_pos(ConfigControlElement *config, u32 idx) {
    struct Position ret;
    switch (config->anchor[idx]) {
        case CONTROL_ELEMENT_LEFT:
            ret.x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(config->x[idx]) << 2;
            ret.y = config->y[idx];
            break;
        case CONTROL_ELEMENT_RIGHT:
            ret.x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(config->x[idx]) << 2;
            ret.y = config->y[idx];
            break;
        case CONTROL_ELEMENT_CENTER:
            ret.x = SCREEN_WIDTH_API / 2;
            ret.y = config->y[idx];
            break;
        case CONTROL_ELEMENT_HIDDEN:
        default:
            ret.x = HIDE_POS;
            ret.y = HIDE_POS;
            break;
    }
    if (djui_panel_is_active()) ret.y = HIDE_POS;
    return ret;
}

void touch_down(struct TouchEvent* event) {
    struct Position pos;
    s32 size;
    for(int i = 0; i < ControlElementsLength; i++) {
        if (ControlElements[i].touchID == 0) {
            pos = get_pos(&configControlElements[i], 0);
            if (pos.y == HIDE_POS) continue;
            size = configControlElements[i].size[0];
            switch (ControlElements[i].type) {
                case Joystick:
                    if (TRIGGER_DETECT(size)) {
                        ControlElements[i].touchID = event->touchID;
                        ControlElements[i].joyX = CORRECT_TOUCH_X(event->x) - pos.x;
                        ControlElements[i].joyY = CORRECT_TOUCH_Y(event->y) - pos.y;
                    }
                    break;
                case Mouse:
                    break;
                case Button:
                    if (TRIGGER_DETECT(size)) {
                        ControlElements[i].touchID = event->touchID;
                        // messy
                        if (ControlElements[i].buttonID == CHAT_BUTTON)
                            djui_interactable_on_key_down(configKeyChat[0]);
                        if (ControlElements[i].buttonID == PLAYERLIST_BUTTON)
                            djui_interactable_on_key_down(configKeyPlayerList[0]);
                    }
                    break;
            }
        }
    }
}

void touch_motion(struct TouchEvent* event) {
    // Mouselook
    struct Position pos = get_pos(&configControlElements[TOUCH_MOUSE], 0);
    s32 size = configControlElements[TOUCH_MOUSE].size[0];
    if (timer != gGlobalTimer && TRIGGER_DETECT(size)) {
        if (before_x > 0)
            touch_x = CORRECT_TOUCH_X(event->x) - before_x;
        before_x = CORRECT_TOUCH_X(event->x);
        if (before_y > 0)
            touch_y = CORRECT_TOUCH_Y(event->y) - before_y;
        if (touch_x < configStickDeadzone / 4)
            touch_x = 0;
        if (touch_y < configStickDeadzone / 4)
            touch_y = 0;
        before_y = CORRECT_TOUCH_Y(event->y);
        timer = gGlobalTimer;
    }
    // Everything else
    for(int i = 0; i < ControlElementsLength; i++) {
        pos = get_pos(&configControlElements[i], 0);
        if (pos.y == HIDE_POS) continue;
        size = configControlElements[i].size[0];
        if (ControlElements[i].touchID == event->touchID) {
            switch (ControlElements[i].type) {
                case Joystick:
                    ; //workaround
                    s32 x,y;
                    x = CORRECT_TOUCH_X(event->x) - pos.x;
                    y = CORRECT_TOUCH_Y(event->y) - pos.y;
                    if (pos.x + size / 2 < CORRECT_TOUCH_X(event->x))
                        x = size / 2;
                    if (pos.x - size / 2 > CORRECT_TOUCH_X(event->x))
                        x = - size / 2;
                    if (pos.y + size / 2 < CORRECT_TOUCH_Y(event->y))
                        y = size / 2;
                    if (pos.y - size / 2 > CORRECT_TOUCH_Y(event->y))
                        y = - size / 2;
                    ControlElements[i].joyX = x;
                    ControlElements[i].joyY = y;
                    break;
                case Mouse:
                    break;
                case Button:
                    if (ControlElements[i].slideTouch && !TRIGGER_DETECT(size)) {
                        ControlElements[i].slideTouch = 0;
                        ControlElements[i].touchID = 0;
                    }
                    break;
            }
        }
        else {
            switch (ControlElements[i].type) {
                case Joystick:
                    break;
                case Mouse:
                    break;
                case Button:
                    if (TRIGGER_DETECT(size)) {
                        ControlElements[i].slideTouch = 1;
                        ControlElements[i].touchID = event->touchID;
                        if (ControlElements[i].buttonID == CHAT_BUTTON)
                            djui_interactable_on_key_down(configKeyChat[0]);
                        if (ControlElements[i].buttonID == PLAYERLIST_BUTTON)
                            djui_interactable_on_key_down(configKeyPlayerList[0]);
                    }
                    break;
            }
        }
    }
}

static void handle_touch_up(struct TouchEvent* event, int i) { // separated for when the layout changes
    ControlElements[i].touchID = 0;
    struct Position pos = get_pos(&configControlElements[i], 0);
    s32 size = configControlElements[i].size[0];
    if (pos.y == HIDE_POS) return;
    switch (ControlElements[i].type) {
        case Joystick:
            ControlElements[i].joyX = 0;
            ControlElements[i].joyY = 0;
            break;
        case Mouse:
            break;
        case Button:
            if (ControlElements[i].buttonID == CHAT_BUTTON)
                djui_interactable_on_key_up(configKeyChat[0]);
            if (ControlElements[i].buttonID == PLAYERLIST_BUTTON)
                djui_interactable_on_key_up(configKeyPlayerList[0]);
            break;
    }
}

void touch_up(struct TouchEvent* event) {
    // Mouselook
    struct Position pos = get_pos(&configControlElements[TOUCH_MOUSE], 0);
    s32 size = configControlElements[TOUCH_MOUSE].size[0];
    if (gGlobalTimer - timer > 1 || TRIGGER_DETECT(size)) {
        touch_x = before_x = 0;
        touch_y = before_y = 0;
    }
    // Everything else
    for(int i = 0; i < ControlElementsLength; i++) {
        if (ControlElements[i].touchID == event->touchID) {
            handle_touch_up(event, i);
        }
    }
}

ALIGNED8 static const u8 texture_button[] = {
#include "textures/touchcontrols/touch_button.rgba16.inc.c"
};

ALIGNED8 static const u8 texture_button_dark[] = {
#include "textures/touchcontrols/touch_button_dark.rgba16.inc.c"
};

// Sprite drawing code stolen from src/game/print.c

static void select_button_texture(int dark) {
    gDPPipeSync(gDisplayListHead++);
    
    if (!dark) {
        gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_button);
    } else {
        gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture_button_dark);
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_load_tex_block);
}

static void select_char_texture(u8 num) {
    const u8 *const *glyphs = segmented_to_virtual(main_hud_lut);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, glyphs[num - 87]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_load_tex_block);
}

static void DrawSprite(s32 x, s32 y, int scaling) {
    gSPTextureRectangle(gDisplayListHead++, x - (15 << scaling), y - (15 << scaling), x + (15 << scaling),
                        y + (15 << scaling), G_TX_RENDERTILE, 0, 0, 4 << (11 - scaling), 1 << (11 - scaling));
}

void render_touch_controls(void) {
    Mtx *mtx;

    mtx = alloc_display_list(sizeof(*mtx));

    if (mtx == NULL) {
        return;
    }

    guOrtho(mtx, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
    gSPPerspNormalize((Gfx *) (gDisplayListHead++), 0xFFFF);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);

    struct Position pos;
    s32 size;
    for (int i = 0; i < ControlElementsLength; i++) {
        pos = get_pos(&configControlElements[i], 0);
        if (pos.y == HIDE_POS) continue;
        size = configControlElements[i].size[0];
        select_button_texture(0);
        switch (ControlElements[i].type) {
            case Joystick:
                DrawSprite(pos.x, pos.y, 3);
                DrawSprite(pos.x + 4 + ControlElements[i].joyX, pos.y + 4 + ControlElements[i].joyY, 2);
                break;
            case Mouse:
                if (before_x > 0 || before_y > 0) {
                    touch_cam_last_x = before_x > 0 ? before_x : touch_cam_last_x;
                    touch_cam_last_y = before_y > 0 ? before_y : touch_cam_last_y;
                    DrawSprite(touch_cam_last_x, touch_cam_last_y, 2);
                }
                break;
            case Button:
                if (ControlElements[i].touchID)
                    select_button_texture(1);
                DrawSprite(pos.x - 8, pos.y, 1 + size / 100);
                select_char_texture(ControlElements[i].character);
                DrawSprite(pos.x, pos.y, size / 100);
                break;
        }
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

static void touchscreen_init(void) {
    for (int i = 0; i < ControlElementsLength; i++) {
        ControlElements[i].touchID = 0;
        ControlElements[i].joyX = 0;
        ControlElements[i].joyY = 0;
        ControlElements[i].slideTouch = 0;
    }
}

static void touchscreen_read(OSContPad *pad) {
    struct Position pos;
    s32 size;
    for(int i = 0; i < ControlElementsLength; i++) {
        pos = get_pos(&configControlElements[i], 0);
        if (pos.y == HIDE_POS) continue;
        size = configControlElements[i].size[0];
        switch (ControlElements[i].type) {
            case Joystick:
                if (ControlElements[i].joyX || ControlElements[i].joyY) {
                    pad->stick_x = (ControlElements[i].joyX + size / 2) * 255 / size - 128;
                    pad->stick_y = (-ControlElements[i].joyY + size / 2) * 255 / size - 128; //inverted for some reason
                }
                break;
            case Mouse:
                break;
            case Button:
                if (ControlElements[i].touchID &&
                    ControlElements[i].buttonID != CHAT_BUTTON &&
                    ControlElements[i].buttonID != PLAYERLIST_BUTTON) {
                    pad->button |= ControlElements[i].buttonID;
                }
                break;
        }
    }
}

static u32 touchscreen_rawkey(void) { //dunno what this does but I'll skip it for now
    return VK_INVALID;
}

struct ControllerAPI controller_touchscreen = {
    0,
    touchscreen_init,
    touchscreen_read,
    touchscreen_rawkey,
    NULL,
    NULL,
    NULL,
    NULL
};
#endif
