// tumbling_bridge.c.inc

#include "levels/wf/header.h"
#include "levels/bbh/header.h"
#include "levels/lll/header.h"
#include "levels/bitfs/header.h"

struct Struct8032F34C sTumblingBridgeParams[] = {
    { 9, -512, 0x80, MODEL_WF_TUMBLING_BRIDGE_PART, wf_seg7_collision_tumbling_bridge },
    { 9, -412, 103, MODEL_BBH_TUMBLING_PLATFORM_PART, bbh_seg7_collision_07026B1C },
    { 9, -512, 0x80, MODEL_LLL_FALLING_PLATFORM, lll_seg7_collision_0701D21C },
    { 9, -512, 0x80, MODEL_BITFS_TUMBLING_PLATFORM_PART, bitfs_seg7_collision_07015288 }
};

void bhv_tumbling_bridge_platform_loop(void) {
    if (!network_sync_object_initialized(o)) {
        struct SyncObject* so = network_init_object(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            network_init_object_field_with_size(o, &o->activeFlags, 16);
            network_init_object_field(o, &o->oAction);
            network_init_object_field(o, &o->oPosX);
            network_init_object_field(o, &o->oPosY);
            network_init_object_field(o, &o->oPosZ);
            network_init_object_field(o, &o->oVelX);
            network_init_object_field(o, &o->oVelY);
            network_init_object_field(o, &o->oVelZ);
            network_init_object_field(o, &o->oFaceAnglePitch);
            network_init_object_field(o, &o->oFaceAngleYaw);
            network_init_object_field(o, &o->oFaceAngleRoll);
        }
    }

    if (o->parentObj != NULL && gCurrCourseNum == COURSE_LLL) {
        if (o->parentObj->oIntangibleTimer == -1) {
            cur_obj_hide();
            o->oIntangibleTimer = o->parentObj->oIntangibleTimer;
        } else {
            cur_obj_unhide();
            o->oIntangibleTimer = o->parentObj->oIntangibleTimer;
        }
    }
    switch (o->oAction) {
        case 0:
            if ((o->oInteractStatus & INT_STATUS_INTERACTED) || gMarioStates[0].marioObj->platform == o) {
                o->oAction++;
                o->oTumblingBridgeUnkF4 = random_sign() * 0x80;
                if (!(o->oInteractStatus & INT_STATUS_INTERACTED)) {
                    network_send_collect_item(o);
                }
                o->oInteractStatus &= ~INT_STATUS_INTERACTED;
            }
            break;
        case 1:
            cur_obj_update_floor_height();
            if (o->oTimer > 5) {
                o->oAction++;
                cur_obj_play_sound_2(SOUND_GENERAL_PLATFORM);
            }
            break;
        case 2:
            if (o->oAngleVelPitch < 0x400)
                o->oAngleVelPitch += 0x80;
            if (o->oAngleVelRoll > -0x400 && o->oAngleVelRoll < 0x400)
                o->oAngleVelRoll += o->oTumblingBridgeUnkF4; // acceleration?
            o->oGravity = -3.0f;
            cur_obj_rotate_face_angle_using_vel();
            cur_obj_move_using_fvel_and_gravity();
            if (o->oPosY < o->oFloorHeight - 300.0f) {
                o->oAction++;
                network_send_object(o);
            }
            break;
        case 3:
            break;
    }
    if (o->parentObj->oAction == 3) {
        obj_mark_for_deletion(o);
        network_send_object(o);
    }

    if (o->parentObj != NULL && o->parentObj->oIntangibleTimer != -1) {
        load_object_collision_model();
    } else if (gCurrCourseNum != COURSE_LLL) {
        load_object_collision_model();
    }
}

void tumbling_bridge_act_1(void) {
    struct Object *platformObj;
    s32 i;
    s32 bridgeID = o->oBehParams2ndByte;
    s32 relativePlatformX;
    s32 relativePlatformZ;
    s32 relativePlatformY = 0;
    s32 relativeInitialPlatformY = 0;

    for (i = 0; i < sTumblingBridgeParams[bridgeID].numBridgeSections; i++) {
        relativePlatformX = 0;
        relativePlatformZ = 0;

        if (bridgeID == 3)
            relativePlatformX = sTumblingBridgeParams[bridgeID].bridgeRelativeStartingXorZ
                                + sTumblingBridgeParams[bridgeID].platformWidth * i;
        else
            relativePlatformZ = sTumblingBridgeParams[bridgeID].bridgeRelativeStartingXorZ
                                + sTumblingBridgeParams[bridgeID].platformWidth * i;

        if (cur_obj_has_behavior(bhvLllTumblingBridge)) {
            if (i % 3 == 0)
                relativePlatformY -= 150;
            relativeInitialPlatformY = 450;
        }

        platformObj = spawn_object_relative(
            0, relativePlatformX, relativePlatformY + relativeInitialPlatformY, relativePlatformZ, o,
            sTumblingBridgeParams[bridgeID].model, bhvTumblingBridgePlatform);
        if (platformObj == NULL) { continue; }
        obj_set_collision_data(platformObj, sTumblingBridgeParams[bridgeID].segAddr);
    }

    o->oAction = 2;
}

void tumbling_bridge_act_2(void) {
    struct Object* player = nearest_player_to_object(o);
    int distanceToPlayer = dist_between_objects(o, player);

    cur_obj_hide();
    if (cur_obj_has_behavior(bhvLllTumblingBridge))
        cur_obj_unhide();
    else if (distanceToPlayer > 1200.0f) {
        o->oAction = 3;
        cur_obj_unhide();
    }
}

void tumbling_bridge_act_3(void) {
    cur_obj_unhide();
    o->oAction = 0;
}

void tumbling_bridge_act_0(void) {
    struct Object* player = nearest_player_to_object(o);
    int distanceToPlayer = dist_between_objects(o, player);

    if (cur_obj_has_behavior(bhvLllTumblingBridge) || distanceToPlayer < 1000.0f)
        o->oAction = 1;
}

void (*sTumblingBridgeActions[])(void) = { tumbling_bridge_act_0, tumbling_bridge_act_1,
                                           tumbling_bridge_act_2, tumbling_bridge_act_3 };

s16 D_8032F38C[] = { -51, 0,     0, -461, 0,   0, -512, 0,   0,    -2611, 0,
                     0,   -2360, 0, 0,    214, 0, 0,    -50, 1945, 1,     0 };

void bhv_tumbling_bridge_loop(void) {
    if (!network_sync_object_initialized(o)) {
        struct SyncObject* so = network_init_object(o, SYNC_DISTANCE_ONLY_EVENTS);
        if (so) {
            network_init_object_field(o, &o->oIntangibleTimer);
        }
    }

    cur_obj_call_action_function(sTumblingBridgeActions);
}
