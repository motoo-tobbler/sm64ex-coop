#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "src/game/interaction.h"
#include "src/engine/math_util.h"

#define RESERVATION_COUNT 10

void network_send_reservation_request(void) {
    assert(networkType == NT_CLIENT);

    struct Packet p;
    packet_init(&p, PACKET_RESERVATION_REQUEST, true);
    network_send(&p);
}

void network_receive_reservation_request(struct Packet* p) {
    assert(networkType == NT_SERVER);
    network_send_reservation();
}

void network_send_reservation(void) {
    assert(networkType == NT_SERVER);
    int clientPlayerIndex = 1; // two-player hack

    // find all reserved objects
    u8 reservedObjs[RESERVATION_COUNT] = { 0 };
    int reservedIndex = 0;
    for (int i = 1; i < MAX_SYNC_OBJECTS; i++) {
        if (syncObjects[i].reserved == clientPlayerIndex) {
            reservedObjs[reservedIndex++] = i;
            if (reservedIndex >= RESERVATION_COUNT) { break; }
        }
    }

    if (reservedIndex < RESERVATION_COUNT) {
        // reserve the rest
        for (int i = MAX_SYNC_OBJECTS - 1; i > 0; i--) {
            if (syncObjects[i].o != NULL) { continue; }
            if (syncObjects[i].reserved != 0) { continue; }
            syncObjects[i].reserved = clientPlayerIndex;
            reservedObjs[reservedIndex++] = i;
            if (reservedIndex >= RESERVATION_COUNT) { break; }
        }
    }

    struct Packet p;
    packet_init(&p, PACKET_RESERVATION, true);
    packet_write(&p, reservedObjs, sizeof(u8) * RESERVATION_COUNT);
    network_send(&p);
}

void network_receive_reservation(struct Packet* p) {
    assert(networkType == NT_CLIENT);
    int clientPlayerIndex = 1; // two-player hack

    // find all reserved objects
    u8 reservedObjs[RESERVATION_COUNT] = { 0 };
    packet_read(p, reservedObjs, sizeof(u8) * RESERVATION_COUNT);

    for (int i = 0; i < RESERVATION_COUNT; i++) {
        int index = reservedObjs[i];
        printf(" %d", index);
        if (index == 0) { continue; }
        if (syncObjects[index].o != NULL) { continue; }
        syncObjects[index].reserved = clientPlayerIndex;
    }
    printf("\n");
}
