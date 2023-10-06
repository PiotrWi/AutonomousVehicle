#pragma once

#include <any>

namespace image_processing
{

class IPipelineEntity
{
public:
    virtual void init() = 0;
    virtual void execute() = 0;
    virtual ~IPipelineEntity() = default;
};

class IProducerPipelineEntity : public virtual IPipelineEntity
{
public:
    virtual std::any get(int outputPort) = 0;
    ~IProducerPipelineEntity() override = default;
};

class IConsumerPipelineEntity : public virtual IPipelineEntity
{
public:
    virtual void setInput(int inputPort, IProducerPipelineEntity*, int producerOutputPort) = 0;
    ~IConsumerPipelineEntity() override = default;
};

}  // namespace image_processing
