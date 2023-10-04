#pragma once

#include <stdexcept>
#include <memory>
#include <vector>

#include "Components/Component.hpp"
#include "Application.hpp"

void createComponentsBasedOnParserInput(int argc, char** argv, Application& applicationContext);
