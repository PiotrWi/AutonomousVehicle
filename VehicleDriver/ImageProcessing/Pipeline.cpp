#include "Pipeline.hpp"
#include <Tools/ExecutionTimeMeasurement.hpp>

namespace image_processing
{

PipeLineBuilder& PipeLineBuilder::add(IProducerPipelineEntity *producer, const std::string& name)
{
    pipelineTasks_.emplace_back(producer, name);
    return *this;
}

PipeLineBuilder& PipeLineBuilder::add(IConsumerPipelineEntity *consumer, const std::string& name,
                          std::vector<PipelinePortMappings>&& portMapping)
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
    return *this;
}

PipeLineBuilder& PipeLineBuilder::add(IConsumerPipelineEntity *consumer, const std::string &name, DefaultMapping)
{
    if (pipelineTasks_.empty())
    {
        throw ProducerInstanceNotFindInPipeline();
    }
    auto lastlyAddedProducer = pipelineTasks_.back().first;
    consumer->setInput(0, dynamic_cast<IProducerPipelineEntity *>(lastlyAddedProducer), 0);

    pipelineTasks_.emplace_back(consumer, name);
    return *this;
}

std::unique_ptr<Pipeline> PipeLineBuilder::build()
{
    return std::make_unique<Pipeline>(std::move(pipelineTasks_));
}

PipeLineBuilderWithPrefix::PipeLineBuilderWithPrefix(std::string prefix)
        : prefix_(prefix)
{
}

PipeLineBuilderWithPrefix& PipeLineBuilderWithPrefix::add(IProducerPipelineEntity* producer)
{
    PipeLineBuilder::add(producer, prefix_ + producer->getDefaultName());
    return *this;
}
PipeLineBuilderWithPrefix& PipeLineBuilderWithPrefix::add(IConsumerPipelineEntity* consumer, std::vector<PipelinePortMappings>&& portMapping)
{
    PipeLineBuilder::add(consumer, prefix_ + consumer->getDefaultName(), std::move(portMapping));
    return *this;
}
PipeLineBuilderWithPrefix& PipeLineBuilderWithPrefix::add(IConsumerPipelineEntity* consumer, DefaultMapping df)
{
    PipeLineBuilder::add(consumer, prefix_ + consumer->getDefaultName(), df);
    return *this;
}

Pipeline::Pipeline(std::vector<std::pair<IPipelineEntity *, std::string>> &&pipelineTasks)
        : pipelineTasks_(std::move(pipelineTasks))
{
}

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

Pipeline::~Pipeline()
{
    for (auto &&[task, name]: pipelineTasks_)
    {
        delete task;
    }
}

std::any Pipeline::getOut() const
{
    return dynamic_cast<IProducerPipelineEntity *>(pipelineTasks_.back().first)->get(0);
}

std::any Pipeline::getOut(std::string in, int port) const
{
    for (auto &&[task, name]: pipelineTasks_)
    {
        if (name == in)
        {
            return dynamic_cast<IProducerPipelineEntity *>(task)->get(port);
        }
    }
    return {};
}

}  // namespace image_processing
