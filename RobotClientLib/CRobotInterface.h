#pragma once

extern "C"
{

void c_init();
bool c_connect();
void c_disconnect();
bool c_isConnected();
void c_subscribeForConnectionStatus(void (*callback)(bool));

struct Speed
{
    int leftWheel;
    int rightWheel;
};

void c_setRequestedSpeed(Speed);
Speed c_getRequestedSpeed();
void c_subscribeForRequestedSpeedChange(void(*callback)(Speed));

}  // extern "C"