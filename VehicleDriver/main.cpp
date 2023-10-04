#include "InputArgumentsParser.hpp"
#include "ApplicationContext.hpp"
#include <Application.hpp>

int main(int argc, char** argv)
{
    Application app;
    createComponentsBasedOnParserInput(argc, argv, app);

    app.start();
    return 0;
}
