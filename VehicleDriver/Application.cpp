#include "Application.hpp"

void Application::start()
{
    applicationContext.accessPoint_.start();

    for (auto&& component : components_)
    {
        component->start();
    }

    while (true)
    {
        applicationContext.eventLoop_.dispatchEvent();
    }
}

void Application::addComponent(std::unique_ptr<components::Component> &&component)
{
    components_.emplace_back(std::move(component));
}

ApplicationContext &Application::getApplicationContext()
{
    return applicationContext;
}

bool Application::isValid()
{
    return not components_.empty();
}
