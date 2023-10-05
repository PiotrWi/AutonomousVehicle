#pragma once

#include <any>
#include <array>

#include "IPipelineEntity.hpp"

namespace image_processing
{

template <typename TArg>
class SingleInputConsumer_1 : public IConsumerPipelineEntity
{
public:
    void execute() override
    {
        TArg* arg = std::any_cast<TArg*>(producerOutputsReferences_[0].first->get(producerOutputsReferences_[0].second));
        execute(*arg);
    }
    void setInput(int inputPort, IProducerPipelineEntity * producer, int producerOutputPort) override
    {
        producerOutputsReferences_[inputPort] = {producer, producerOutputPort};
    }
private:
    virtual void execute(TArg& arg) = 0;

    std::array<std::pair<IProducerPipelineEntity*, int>, 1> producerOutputsReferences_;
};

}  // namespace image_processing