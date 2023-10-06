#pragma once

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

class Pipeline
{
public:
    void init();
    void execute();
    void add(IProducerPipelineEntity* producer, const std::string& name);
    void add(IConsumerPipelineEntity* producer, const std::string& name,
             std::vector<PipelinePortMappings> portMapping);
private:
    std::vector<std::pair<IPipelineEntity*, std::string>> pipelineTasks_;
};

}  // namespace image_processing
