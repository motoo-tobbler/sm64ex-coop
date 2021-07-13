#include <stdio.h>
#include "djui.h"
#include "pc/network/network.h"
#include "pc/utils/misc.h"
#include "pc/configfile.h"

#ifdef DISCORD_SDK
#define DJUI_HOST_NS_IS_SOCKET (configNetworkSystem == 1)
#else
#define DJUI_HOST_NS_IS_SOCKET (true)
#endif

struct DjuiInputbox* sInputboxPort = NULL;

static void djui_panel_host_network_system_change(struct DjuiBase* base) {
    struct DjuiSelectionbox* selectionbox = (struct DjuiSelectionbox*)base;
    djui_base_set_enabled(&sInputboxPort->base, DJUI_HOST_NS_IS_SOCKET);
}

static bool djui_panel_host_port_valid(void) {
    char* buffer = sInputboxPort->buffer;
    int port = 0;
    while (*buffer != '\0') {
        if (*buffer < '0' || *buffer > '9') { return false; }
        port *= 10;
        port += (*buffer - '0');
        buffer++;
    }
    return port >= 1024 && port <= 65535;
}

static void djui_panel_host_port_text_change(struct DjuiBase* caller) {
    struct DjuiInputbox* inputbox1 = (struct DjuiInputbox*)caller;
    if (djui_panel_host_port_valid()) {
        djui_inputbox_set_text_color(inputbox1, 0, 0, 0, 255);
    } else {
        djui_inputbox_set_text_color(inputbox1, 255, 0, 0, 255);
    }
}

static void djui_panel_host_do_host(struct DjuiBase* caller) {
    if (!djui_panel_host_port_valid()) {
        djui_interactable_set_input_focus(&sInputboxPort->base);
        djui_inputbox_select_all(sInputboxPort);
        return;
    }
    configHostPort = atoi(sInputboxPort->buffer);
    djui_panel_host_message_create(caller);
}

void djui_panel_host_create(struct DjuiBase* caller) {
#ifdef DISCORD_SDK
    f32 bodyHeight = 32 * 5 + 64 * 2 + 16 * 7;
#else
    f32 bodyHeight = 32 * 4 + 64 * 2 + 16 * 6;
#endif

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\H\\#1be700\\O\\#00b3ff\\S\\#ffef00\\T");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);
    {
#ifdef DISCORD_SDK
        char* nChoices[2] = { "Discord", "Direct Connection" };
        struct DjuiSelectionbox* selectionbox1 = djui_selectionbox_create(&body->base, "Network system", nChoices, 2, &configNetworkSystem);
        djui_base_set_size_type(&selectionbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox1->base, 1.0f, 32);
        djui_interactable_hook_value_change(&selectionbox1->base, djui_panel_host_network_system_change);
#endif

        struct DjuiRect* rect1 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect1->base, 1.0f, 32);
        djui_base_set_color(&rect1->base, 0, 0, 0, 0);
        {
            struct DjuiText* text1 = djui_text_create(&rect1->base, "Port");
            djui_base_set_size_type(&text1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_color(&text1->base, 200, 200, 200, 255);
            djui_base_set_size(&text1->base, 0.485f, 64);
            djui_base_set_alignment(&text1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);

            struct DjuiInputbox* inputbox1 = djui_inputbox_create(&rect1->base, 32);
            djui_base_set_size_type(&inputbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&inputbox1->base, 0.5f, 32);
            djui_base_set_alignment(&inputbox1->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            char portString[32] = { 0 };
            snprintf(portString, 32, "%d", configHostPort);
            djui_inputbox_set_text(inputbox1, portString);
            djui_interactable_hook_value_change(&inputbox1->base, djui_panel_host_port_text_change);
#ifdef DISCORD_SDK
            djui_base_set_enabled(&inputbox1->base, DJUI_HOST_NS_IS_SOCKET);
#endif
            sInputboxPort = inputbox1;
        }

        char* iChoices[3] = { "Non-solid", "Solid", "Friendly Fire" };
        struct DjuiSelectionbox* selectionbox2 = djui_selectionbox_create(&body->base, "Player interaction", iChoices, 3, &configFiltering);
        djui_base_set_size_type(&selectionbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&selectionbox2->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, "Stay in level after star", &configStayInLevelAfterStar);
        djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox1->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox2 = djui_checkbox_create(&body->base, "Play intro cutscene", &configSkipIntro);
        djui_base_set_size_type(&checkbox2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox2->base, 1.0f, 32);

        struct DjuiCheckbox* checkbox3 = djui_checkbox_create(&body->base, "Share lives", &configShareLives);
        djui_base_set_size_type(&checkbox3->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&checkbox3->base, 1.0f, 32);

        struct DjuiRect* rect2 = djui_rect_create(&body->base);
        djui_base_set_size_type(&rect2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&rect2->base, 1.0f, 64);
        djui_base_set_color(&rect2->base, 0, 0, 0, 0);
        {
            struct DjuiButton* button1 = djui_button_create(&rect2->base, "Back");
            djui_base_set_size_type(&button1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button1->base, 0.485f, 64);
            djui_base_set_alignment(&button1->base, DJUI_HALIGN_LEFT, DJUI_VALIGN_TOP);
            djui_button_set_style(button1, 1);
            djui_interactable_hook_click(&button1->base, djui_panel_menu_back);

            struct DjuiButton* button2 = djui_button_create(&rect2->base, "Host");
            djui_base_set_size_type(&button2->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&button2->base, 0.485f, 64);
            djui_base_set_alignment(&button2->base, DJUI_HALIGN_RIGHT, DJUI_VALIGN_TOP);
            djui_interactable_hook_click(&button2->base, djui_panel_host_do_host);
            defaultBase = &button2->base;
        }
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}
