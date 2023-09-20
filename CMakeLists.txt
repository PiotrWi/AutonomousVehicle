cmake_minimum_required(VERSION 3.25)
project(Autonomous_vehicle)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(OpenCV)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror -std=c++20")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(drivers STATIC
        Drivers/GpioDriver.cpp
        Drivers/GpioDriver.hpp
        Drivers/MotorsDriver.cpp
        Drivers/MotorsDriver.hpp
        Drivers/PwmDriver.cpp
        Drivers/PwmDriver.hpp
        Drivers/SysHelper.hpp
        Drivers/SysHelper.cpp
        Drivers/FDRaiiWrapper.cpp
        Drivers/FDRaiiWrapper.hpp
)

add_executable(Autonomous_vehicle main.cpp
        InputArgumentsParser.hpp
        InputArgumentsParser.cpp
        Components/Component.hpp
        Components/VideoProccessingComponent.cpp
        Components/VideoProccessingComponent.hpp
        ImageProcessing/ImageOperators.hpp
        ImageProcessing/RoadLineDetection.hpp
        ImageProcessing/HoughtOperators.hpp
        ImageProcessing/HoughtOperators.cpp
        ImageProcessing/RoadLineDetection.cpp
        Components/CameraProcessingComponent.cpp
        Components/CameraProcessingComponent.hpp
        Components/MotorTestComponents.cpp
        Components/MotorTestComponents.hpp
        tools/StringAlgorithms.hpp
        tools/StringAlgorithms.cpp
)

target_link_libraries(Autonomous_vehicle boost_program_options opencv_highgui drivers)

add_subdirectory(test EXCLUDE_FROM_ALL)