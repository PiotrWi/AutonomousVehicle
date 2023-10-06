#pragma once

#include <vector>
#include <memory>
#include "../../Tools/SingletonAddOn.hpp"

namespace gui_controller
{

class EnableAble
{
public:
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual ~EnableAble() = default;
};

template<typename TObject>
class EnableAbleImpl : public EnableAble
{
public:
    explicit EnableAbleImpl(TObject *object)
            : object_(object)
    {
    }
    void enable() override
    {
        object_->setEnabled(true);
    }
    void disable() override
    {
        object_->setEnabled(false);
    }
private:
    TObject *object_;
};

struct EnabledWhenConnectionUp{};
struct EnabledWhenConnectionDown{};

class SetEnableManager : public SingletonAddOn<SetEnableManager>
{
public:
    template<class Item>
    void registerItem(Item* object, EnabledWhenConnectionUp)
    {
        objectWhenConnectionIsActive_.push_back(std::make_unique<EnableAbleImpl<Item>>(object));
    }

    template<class Item>
    void registerItem(Item* object, EnabledWhenConnectionDown)
    {
        objectWhenConnectionIsUnActive_.push_back(std::make_unique<EnableAbleImpl<Item>>(object));
    }

    void reactOnConnected();
    void reactOnDisconnected();
private:
    std::vector<std::unique_ptr<EnableAble>> objectWhenConnectionIsActive_;
    std::vector<std::unique_ptr<EnableAble>> objectWhenConnectionIsUnActive_;
};

}  // namespace gui_controller
