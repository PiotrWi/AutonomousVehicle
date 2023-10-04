#pragma once

#include <any>

namespace image_processing
{

class IPipelineEntity
{
public:
    virtual void init() = 0;
    virtual void execute() = 0;
    virtual ~IPipelineEntity() {}
};

class IProducerPipelineEntity : public IPipelineEntity
{
public:
    virtual std::any get(int outputPort) = 0;
    virtual ~IProducerPipelineEntity() {}
};

class IConsumerPipelineEntity : public IPipelineEntity
{
public:
    virtual void setInput(int inputPort, IProducerPipelineEntity*, int producerOutputPort) = 0;
    virtual ~IConsumerPipelineEntity() {}
};

}  // namespace image_processing
