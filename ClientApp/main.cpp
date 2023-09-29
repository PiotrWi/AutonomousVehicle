#include <QApplication>

#include "Gui/MainApplication.hpp"

#include "../RobotClientLib/RobotInterface.hpp"

int main(int argc, char** argv)
{
    robot_interface::init();

    QApplication app(argc, argv);
    MainApplication window;
    window.show();
    return app.exec();
}
