#pragma once

namespace robot_interface
{

struct Speed
{
    int leftWheel;
    int rightWheel;
};

struct IntegerPicture
{
    int format;
    int rows;
    int columns;
    std::vector<unsigned char> pixels;
};

enum class CameraSide
{
    Left,
    Right,
};

}  // namespace robot_interface
