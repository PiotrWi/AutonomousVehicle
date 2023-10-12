#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "ImagePipelines/IPipelineEntity.hpp"

namespace image_processing
{

class ProducerInstanceNotFindInPipeline : public std::logic_error
{
public:
    ProducerInstanceNotFindInPipeline()
            : std::logic_error("Producer instance was not added to pipeline before it was to be used. "
                               "Check producer names or order of pipeline population.")
    {}
};

struct PipelinePortMappings
{
    int inputPort;
    std::string producerName;
    int producerOutputPort;
};

struct DefaultMapping {};

class Pipeline;

class PipeLineBuilder
{
public:
    PipeLineBuilder& add(IProducerPipelineEntity* producer, const std::string& name);
    PipeLineBuilder& add(IConsumerPipelineEntity* consumer, const std::string& name, std::vector<PipelinePortMappings>&& portMapping);
    PipeLineBuilder& add(IConsumerPipelineEntity* consumer, const std::string& name, DefaultMapping df = {});
    std::unique_ptr<Pipeline> build();
private:
    std::vector<std::pair<IPipelineEntity*, std::string>> pipelineTasks_;
};

class PipeLineBuilderWithPrefix : public PipeLineBuilder
{
public:
    explicit PipeLineBuilderWithPrefix(std::string prefix);
    PipeLineBuilderWithPrefix& add(IProducerPipelineEntity* producer);
    PipeLineBuilderWithPrefix& add(IConsumerPipelineEntity* consumer, std::vector<PipelinePortMappings>&& portMapping);
    PipeLineBuilderWithPrefix& add(IConsumerPipelineEntity* consumer, DefaultMapping df = {});
private:
    std::string prefix_;
};

class Pipeline
{
public:
    explicit Pipeline(std::vector<std::pair<IPipelineEntity*, std::string>>&& pipelineTasks);
    void init();
    void execute();

    std::any getOut() const;
    std::any getOut(std::string in, int port) const;
    ~Pipeline();
private:
    std::vector<std::pair<IPipelineEntity*, std::string>> pipelineTasks_;
};

}  // namespace image_processing
