#include "InputArgumentsParser.hpp"

int main(int argc, char** argv)
{
    auto components = createComponentsBasedOnParserInput(argc, argv);

    for (auto&& component: components)
    {
        component->start();
    }
    return 0;
}
