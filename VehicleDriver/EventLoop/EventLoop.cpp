#include "EventLoop.hpp"

EventLoop::SubsciptionContext::SubsciptionContext(std::function<void(Event*)> handler, unsigned int id)
    : activeContex_(new ActiveContex(1, true))
    , id_(id)
    , handler_(handler)
{
}

EventLoop::SubsciptionContext::SubsciptionContext(const SubsciptionContext& other)
    : activeContex_(other.activeContex_)
    , id_(other.id_)
    , handler_(other.handler_)
{
    ++activeContex_->refCount_;
}

EventLoop::SubsciptionContext& EventLoop::SubsciptionContext::operator=(const SubsciptionContext& other)
{
    if (this == &other) return *this;
    this->activeContex_ = other.activeContex_;
    handler_ = other.handler_;
    id_ = other.id_;

    ++activeContex_->refCount_;

    return *this;
}

EventLoop::SubsciptionContext::~SubsciptionContext()
{
    --activeContex_->refCount_;
    if (activeContex_->refCount_ == 0)
    {
        delete activeContex_;
    }
}

bool EventLoop::SubsciptionContext::isActive()
{
    return activeContex_->isActive_;
}

unsigned int EventLoop::SubsciptionContext::getId()
{
    return id_;
}

std::function<void()> EventLoop::SubsciptionContext::getClearOperator()
{
    return std::function<void()>([this](){ activeContex_->isActive_ = false; });
}

////

EventLoop::SubsciptionRaii::SubsciptionRaii(std::function<void()> setUnactiveAllLeavingInstances,
                                            std::function<void()> removeFromSubcribents)
    : setUnactiveAllLeavingInstances_(setUnactiveAllLeavingInstances)
    , removeFromSubcribents_(removeFromSubcribents)
{
}

EventLoop::SubsciptionRaii::~SubsciptionRaii()
{
    setUnactiveAllLeavingInstances_();
    removeFromSubcribents_();
}

////

void EventLoop::pushEvent(Event&& event)
{
    std::lock_guard<std::mutex> m(eventsQueueMutex_);
    eventsQueue_.push(std::move(event));
    eventQueue_ConditionVariable_.notify_one();
}

std::unique_ptr<EventLoop::SubsciptionRaii> EventLoop::subscribeForEvent(std::function<void(Event*)> handler, unsigned int eventId)
{
    static unsigned int id = 0;
    subscriptions_[eventId].emplace_back(handler, ++id);

    auto deleter = [this, eventId, clearId = id](){
        auto elem = std::find_if(subscriptions_[eventId].begin(), subscriptions_[eventId].end(), [clearId](auto&& elem){
            return elem.getId() == clearId;
        });
        if (elem != subscriptions_[eventId].end())
            subscriptions_[eventId].erase(elem);
    };

    return std::make_unique<EventLoop::SubsciptionRaii>(
            subscriptions_[eventId].back().getClearOperator(),
            deleter);
}

void EventLoop::dispatchEvent()
{
    std::unique_lock<std::mutex> lk(eventsQueueMutex_);
    eventQueue_ConditionVariable_.wait(lk, [&](){return not eventsQueue_.empty();});
    if (not eventsQueue_.empty())
    {
        auto& event = eventsQueue_.front();

        auto subscribers = subscriptions_[event.getId()];
        for (auto&& subscriber: subscribers)
        {
            if(subscriber.isActive())
            {
                subscriber.handler_(&event);
            }
        }
        eventsQueue_.pop();
    }
}
