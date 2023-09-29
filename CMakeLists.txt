cmake_minimum_required(VERSION 3.25)
project(Autonomous_vehicle)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror -std=c++20")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Tools)
add_subdirectory(VehicleDriver)
add_subdirectory(RobotClientLib)
add_subdirectory(ClientApp)