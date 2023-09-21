#include <QApplication>

#include "MainApplication.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainApplication window;
    window.show();
    return app.exec();
}
