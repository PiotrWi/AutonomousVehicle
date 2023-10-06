find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(
        ${Qt6Widgets_INCLUDE_DIRS}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(ClientApp
        main.cpp
        Gui/MainApplication.cpp
        Gui/MainApplication.hpp
        Gui/QControlPanelView.cpp
        Gui/QControlPanelView.hpp
        GuiController/KeyPressController.cpp
        GuiController/KeyPressController.hpp
        Gui/QCameraView.hpp
        Gui/QCameraView.cpp
        Gui/QLadarVier.hpp
        Gui/QLadarView.cpp
        GuiController/ConnectionController.cpp
        GuiController/ConnectionController.hpp
        GuiController/SetEnableManager.hpp
        ../Tools/SingletonAddOn.hpp
        GuiController/SetEnableManager.cpp
        GuiController/CameraController.cpp
        GuiController/CameraController.hpp
        utils/DumpImages.cpp
        utils/DumpImages.hpp
)

target_link_libraries(ClientApp
        Qt6::Core
        Qt6::Widgets
        AutonomousVehicleInterface
        tools
)
