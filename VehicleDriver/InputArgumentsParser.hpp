#pragma once

#include <stdexcept>
#include <memory>
#include <vector>

#include "Components/Component.hpp"

std::vector<std::unique_ptr<components::Component>> createComponentsBasedOnParserInput(int argc, char** argv);
