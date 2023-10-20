cmake_minimum_required(VERSION 3.18)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(AutonomousVehicleInterface SHARED
        detail/handlers/RequestedSpeed.cpp
        detail/handlers/RequestedSpeed.hpp
        detail/RobotInterface.cpp
        RobotInterface.hpp
        Types.hpp
        CRobotInterface.h
        detail/CRobotInterface.cpp
        detail/handlers/ImageHandler.cpp
        detail/handlers/ImageHandler.hpp
        detail/handlers/IMessageHandler.hpp
)

add_dependencies(AutonomousVehicleInterface CommunicationProtocol_proto_generated)
