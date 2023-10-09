#pragma once

#include <string>
#include <Tools/SingletonAddOn.hpp>

class AppConfig : public SingletonAddOn<AppConfig>
{
public:
    std::string getCameraDumpDirectory();
};