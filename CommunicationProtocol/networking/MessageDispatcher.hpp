#pragma once

#include <functional>
#include <map>
#include <iostream>
#include <string>
#include <vector>

#include "../MessageIds.hpp"
#include "../Message.hpp"
#include <CommunicationProtocol/networking/detail/MessageReconstruct.hpp>

class IGenericHandler
{
public:
    virtual void handle(std::string&& payload) = 0;
    virtual ~IGenericHandler() = default;
};

template <typename TProtoType>
class ConcreteMsgHandler : public IGenericHandler
{
public:
    void handle(std::string&& payload) override
    {
        TProtoType protoMsg;
        auto parsingSuccessful = protoMsg.ParseFromString(payload);
        if (not parsingSuccessful)
        {
            std::cerr << "Unsucessfull parse" << std::endl;
        }
        for (auto& subscriber : clients_)  // Be carefull.
        {
            subscriber(protoMsg);
        }
    }
    void addSubscriber(std::function<void(const TProtoType&)> subscriber)
    {
        clients_.push_back(subscriber);
    }
private:
    std::vector<std::function<void(const TProtoType&)>> clients_;
};

namespace networking
{

class MessageDispatcher
{
public:
    void dispatchMessage(const std::string& message);

    template<class TProtoType>
    void subscribeFor(const std::function<void(const TProtoType&)>& fcn)
    {
        TProtoType tmp;
        auto id = getMsgId(tmp.GetTypeName());
        auto*& concreteHandler = concreteMessageHandlers_[id];
        if (concreteHandler == nullptr)
        {
            concreteHandler = new ConcreteMsgHandler<TProtoType>();
        }
        ((ConcreteMsgHandler<TProtoType>*)(concreteHandler))->addSubscriber(fcn);
    }
private:
    void dispatchToHandler(unsigned int messageType, std::string &payload);

    std::map<unsigned int, IGenericHandler*> concreteMessageHandlers_;
    std::vector<Message> sequencedMessages_;
    MessageReconstruct buffer_;
};

}  // namespace networking
