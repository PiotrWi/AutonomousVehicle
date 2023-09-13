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
        ImageProcessing/RoadLineDetection.cpp)

target_link_libraries(Autonomous_vehicle boost_program_options opencv_highgui)