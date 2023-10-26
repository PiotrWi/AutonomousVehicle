#pragma once

#include <string>
#include <Tools/SingletonAddOn.hpp>

class AppConfig : public SingletonAddOn<AppConfig>
{
public:
    std::string getDumpDirectory() const;
    std::string getLeftCoefficientFileLoc() const;
    std::string getRightCoefficientFileLoc() const;
    int getCameraFps() const;
    int getCameraWidth() const;
    int getCameraHeight() const;
};