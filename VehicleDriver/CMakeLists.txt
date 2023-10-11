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

add_library(imageProcessing STATIC
        ImageProcessing/ImageOperations/ImageOperators.hpp
        ImageProcessing/ImageOperations/RoadLineDetection.hpp
        ImageProcessing/ImageOperations/HoughtOperators.hpp
        ImageProcessing/ImageOperations/HoughtOperators.cpp
        ImageProcessing/ImageOperations/RoadLineDetection.cpp
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
        ImageProcessing/ImagePipelines/FlipImage.cpp
        ImageProcessing/ImagePipelines/FlipImage.hpp
        ImageProcessing/ImagePipelines/DumpImage.cpp
        ImageProcessing/ImagePipelines/DumpImage.hpp
        ImageProcessing/ImagePipelines/CorrectImage.cpp
        ImageProcessing/ImagePipelines/CorrectImage.hpp
        ImageProcessing/Calibration.hpp
)

add_executable(Autonomous_vehicle main.cpp
        Networking/AccessPoint.hpp
        Networking/AccessPoint.cpp
        Networking/Session.cpp
        Networking/Session.hpp
        Networking/MessageSender.hpp
        Networking/MessageSender.cpp
        Components/Component.hpp
        Components/VideoProccessingComponent.cpp
        Components/VideoProccessingComponent.hpp
        Components/CameraProcessingComponent.cpp
        Components/CameraProcessingComponent.hpp
        Components/MotorTestComponents.cpp
        Components/MotorTestComponents.hpp
        Components/RobotComponent.cpp
        Components/RobotComponent.hpp
        Components/CalibrationComponent.cpp
        Components/CalibrationComponent.hpp
        Services/SpeedControlService.cpp
        Services/SpeedControlService.hpp
        InputArgumentsParser.hpp
        InputArgumentsParser.cpp
        ApplicationContext.hpp
        ApplicationContext.cpp
        Application.cpp
        Application.hpp
        Common/ImageTypes.hpp
        AppConfig.hpp
        AppConfig.cpp
)

target_link_libraries(Autonomous_vehicle
        boost_program_options
        opencv_highgui
        opencv_calib3d
        imageProcessing
        drivers
        eventLoop
        tools
        rt)

add_subdirectory(test EXCLUDE_FROM_ALL)
