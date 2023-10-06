cmake_minimum_required(VERSION 3.22)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(AutonomousVehicleInterface SHARED
        detail/networking/MessageDispatcher.cpp
        detail/networking/MessageDispatcher.hpp
        detail/networking/Connection.cpp
        detail/networking/Connection.hpp
        detail/handlers/RequestedSpeed.cpp
        detail/handlers/RequestedSpeed.hpp
        detail/networking/RobotAccessPoint.cpp
        detail/networking/RobotAccessPoint.hpp
        detail/RobotInterface.cpp
        RobotInterface.hpp
        Types.hpp
        CRobotInterface.h
        detail/CRobotInterface.cpp
        detail/handlers/ImageHandler.cpp
        detail/handlers/ImageHandler.hpp
        detail/handlers/IMessageHandler.hpp
)

