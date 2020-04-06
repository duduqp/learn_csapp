#pragma once

typedef struct{
    int state;
    char data[4096];
} packet;

#define MSG_TYPE_A  1
#define MSG_TYPE_B  2
#define MSG_TYPE_HEARTBEAT  3

#define A_TIMEOUT 60
#define B_TIMEOUT 30



