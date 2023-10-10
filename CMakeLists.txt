cmake_minimum_required(VERSION 3.15)
project(Autonomous_vehicle)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DASSERTSON)
    SET(CMAKE_CXX_FLAGS  "-Og -g -std=c++20 -latomic -pthread") # due te opencv internal: -Wall -Wextra -Werror
else()
    SET(CMAKE_CXX_FLAGS  "-Ofast -std=c++20 -flto -latomic -pthread") # due te opencv internal: -Wall -Wextra -Werror
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Tools)
add_subdirectory(VehicleDriver)
add_subdirectory(RobotClientLib)
add_subdirectory(ClientApp)