#pragma once

extern "C"
{

// Connection interfaces
void c_init();
bool c_connect(const char* ip, unsigned int port);
void c_disconnect();
bool c_isConnected();
void c_subscribeForConnectionStatus(void (*callback)(bool));

// Speed interfaces
struct Speed
{
    int leftWheel;
    int rightWheel;
};

void c_setRequestedSpeed(Speed);
Speed c_getRequestedSpeed();
void c_subscribeForRequestedSpeedChange(void(*callback)(Speed));

struct IntegerPicture
{
    int format;
    int rows;
    int columns;
    unsigned char* pixels;

};

// Picture interfaces
enum Side
{
    Left,
    Right
};

void c_free_IntegerPicture(IntegerPicture*);
IntegerPicture c_getPicture(Side);
void c_subscribeForPicture(Side, void(*callback)(IntegerPicture));

}  // extern "C"
