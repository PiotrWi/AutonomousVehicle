cmake_minimum_required(VERSION 3.15)
project(Autonomous_vehicle)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(OpenCV)
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

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
        Drivers/CameraDriver.cpp
        Drivers/CameraDriver.hpp
)

add_library(eventLoop STATIC
        EventLoop/EventIds.hpp
        EventLoop/GuiSpeedRequest.hpp
        EventLoop/Event.hpp
        EventLoop/EventLoop.hpp
        EventLoop/EventLoop.cpp
        EventLoop/Event.cpp
        EventLoop/MessageDecoder.hpp
        EventLoop/MessageDecoder.cpp
        EventLoop/MessageEncoder.hpp
        EventLoop/MessageEncoder.cpp
)

add_executable(Autonomous_vehicle main.cpp
        InputArgumentsParser.hpp
        InputArgumentsParser.cpp
        Components/Component.hpp
        Components/VideoProccessingComponent.cpp
        Components/VideoProccessingComponent.hpp
        ImageProcessing/ImageOperations/ImageOperators.hpp
        ImageProcessing/ImageOperations/RoadLineDetection.hpp
        ImageProcessing/ImageOperations/HoughtOperators.hpp
        ImageProcessing/ImageOperations/HoughtOperators.cpp
        ImageProcessing/ImageOperations/RoadLineDetection.cpp
        Components/CameraProcessingComponent.cpp
        Components/CameraProcessingComponent.hpp
        Components/MotorTestComponents.cpp
        Components/MotorTestComponents.hpp
        Networking/AccessPoint.hpp
        Networking/AccessPoint.cpp
        Networking/Session.cpp
        Networking/Session.hpp
        Components/RobotComponent.cpp
        Components/RobotComponent.hpp
        Services/SpeedControlService.cpp
        Services/SpeedControlService.hpp
        Networking/MessageSender.hpp
        Networking/MessageSender.cpp
        ImageProcessing/Pipeline.hpp
        ImageProcessing/ImagePipelines/IPipelineEntity.hpp
        ImageProcessing/Pipeline.cpp
        ImageProcessing/ImagePipelines/ImageFromCamera.hpp
        ImageProcessing/ImagePipelines/PreviewEntity.hpp
        ImageProcessing/PipelineFactory.hpp
        ImageProcessing/PipelineFactory.cpp
        ImageProcessing/ImagePipelines/ImageFromCamera.cpp
        ImageProcessing/ImagePipelines/PreviewEntity.cpp
        ImageProcessing/ImagePipelines/PicturePublisher.cpp
        ImageProcessing/ImagePipelines/PicturePublisher.hpp
        ImageProcessing/ImagePipelines/SingleInputConsumer.hpp
        ApplicationContext.hpp
        ApplicationContext.cpp
        Application.cpp
        Application.hpp
        Common/ImageTypes.hpp
        ImageProcessing/ImagePipelines/FlipImage.cpp
        ImageProcessing/ImagePipelines/FlipImage.hpp
)

target_link_libraries(Autonomous_vehicle
        boost_program_options
        opencv_highgui
        drivers
        eventLoop
        tools)

add_subdirectory(test EXCLUDE_FROM_ALL)
