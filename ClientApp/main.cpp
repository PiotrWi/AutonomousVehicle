#include <QApplication>

#include "MainApplication.hpp"

#include <Backend/RobotAccessPoint.hpp>

int main(int argc, char** argv)
{
    backend::RobotAccessPoint::getInstance().start();

    QApplication app(argc, argv);
    MainApplication window;
    window.show();
    return app.exec();
}
