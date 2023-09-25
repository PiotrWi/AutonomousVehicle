#include "SetEnableManager.hpp"

namespace gui_controller
{

void SetEnableManager::reactOnConnected()
{
    for (auto&& toEnable : objectWhenConnectionIsActive_)
    {
        toEnable->enable();
    }
    for (auto&& toDisable : objectWhenConnectionIsUnActive_)
    {
        toDisable->disable();
    }
}

void SetEnableManager::reactOnDisconnected()
{
    for (auto&& toEnable : objectWhenConnectionIsUnActive_)
    {
        toEnable->enable();
    }
    for (auto&& toDisable : objectWhenConnectionIsActive_)
    {
        toDisable->disable();
    }
}

}  // namespace gui_controller
