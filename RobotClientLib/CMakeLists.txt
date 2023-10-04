cmake_minimum_required(VERSION 3.22)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(AutonomousVehicleInterface SHARED
        detail/MessageDispatcher.cpp
        detail/MessageDispatcher.hpp
        detail/Connection.cpp
        detail/Connection.hpp
        detail/RequestedSpeed.cpp
        detail/RequestedSpeed.hpp
        detail/RobotAccessPoint.cpp
        detail/RobotAccessPoint.hpp
        detail/RobotInterface.cpp
        RobotInterface.hpp
        Types.hpp
        CRobotInterface.h
        detail/CRobotInterface.cpp
        detail/ImageHandler.cpp
        detail/ImageHandler.hpp
        detail/IMessageHandler.hpp
)

