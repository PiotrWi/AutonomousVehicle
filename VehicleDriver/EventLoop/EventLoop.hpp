#pragma once

#include "Event.hpp"
#include "EventIds.hpp"

#include <functional>
#include <queue>
#include <memory>
#include <mutex>
#include <vector>

class EventLoop
{
    class SubsciptionContext
    {
        friend EventLoop;
    public:
        explicit SubsciptionContext(std::function<void(Event*)> handler, unsigned int id);
        SubsciptionContext(const SubsciptionContext&);
        SubsciptionContext& operator=(const SubsciptionContext&);
        ~SubsciptionContext();

        bool isActive();
        unsigned int getId();
        std::function<void()> getClearOperator();
    private:
        struct ActiveContex
        {
            ActiveContex(int refCount, bool isActive)
                : refCount_(refCount)
                , isActive_(isActive) {}
            int refCount_;
            bool isActive_;
        }* activeContex_;
        unsigned int id_;
    public:
        std::function<void(Event*)> handler_;
    };
    class SubsciptionRaii
    {
    public:
        explicit SubsciptionRaii(std::function<void()> setUnactiveAllLeavingInstances,
                                 std::function<void()> removeFromSubcribents);
        ~SubsciptionRaii();
    private:
        std::function<void()> setUnactiveAllLeavingInstances_;
        std::function<void()> removeFromSubcribents_;
    };

public:
    void pushEvent(Event&&);
    std::unique_ptr<EventLoop::SubsciptionRaii> subscribeForEvent(std::function<void(Event*)> handler, unsigned int eventId);

    template<typename TEvent>
    std::unique_ptr<EventLoop::SubsciptionRaii> subscribeForEvent(std::function<void(Event*)> handler)
    {
        return subscribeForEvent(handler, getId<TEvent>());
    }
    void dispatchEvent();
private:
    std::mutex eventsQueueMutex_;
    std::queue<Event> eventsQueue_;

    std::array<std::vector<SubsciptionContext>, EventsCount> subscriptions_;
};
