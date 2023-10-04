#pragma once

#include <memory>
#include <Components/Component.hpp>
#include <ApplicationContext.hpp>

class Application
{
public:
    void start();
    void addComponent(std::unique_ptr<components::Component>&& component);
    ApplicationContext& getApplicationContext();
    bool isValid();
private:
    ApplicationContext applicationContext;
    std::vector<std::unique_ptr<components::Component>> components_;
};

