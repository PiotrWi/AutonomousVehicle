#include "Pipeline.hpp"
#include <Tools/ExecutionTimeMeasurement.hpp>

namespace image_processing
{

void Pipeline::init()
{
    for (auto &&[task, name]: pipelineTasks_) {
        task->init();
    }
}

void Pipeline::execute()
{
    RaiiMultipleStepExecutionTimeMeasurement timeMeasurement("Pipeline: ");
    for (auto &&[task, name]: pipelineTasks_) {
        task->execute();
        timeMeasurement.step(name.c_str());
    }
}

void Pipeline::add(IProducerPipelineEntity *producer, const std::string& name)
{
    pipelineTasks_.emplace_back(producer, name);
}

void Pipeline::add(IConsumerPipelineEntity *consumer, const std::string& name, std::vector<PipelinePortMappings> portMapping)
{
    pipelineTasks_.emplace_back(consumer, name);
    for (auto &&singleMapping: portMapping) {
        auto producerIt = std::find_if(pipelineTasks_.begin(), pipelineTasks_.end(),
                                       [&singleMapping](auto &&producerToName) {
                                           return producerToName.second == singleMapping.producerName;
                                       });
        if (producerIt == std::end(pipelineTasks_)) {
            throw ProducerInstanceNotFindInPipeline();
        }
        consumer->setInput(singleMapping.inputPort, dynamic_cast<IProducerPipelineEntity *>(producerIt->first),
                           singleMapping.producerOutputPort);
    }
}

}  // namespace image_processing
