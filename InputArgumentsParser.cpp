#include "InputArgumentsParser.hpp"

#include <iostream>
#include <optional>
#include <string>

#include <boost/program_options.hpp>

#include "Components/Component.hpp"
#include "Components/VideoProccessingComponent.hpp"

class ParsingError : public std::runtime_error { public: ParsingError(); };
ParsingError::ParsingError() : std::runtime_error("Parsing error.") {}

using TOptionHandler = std::optional<std::unique_ptr<Component>> (*)(const boost::program_options::variables_map&);

auto getOptionsDescriptions()
{
    boost::program_options::options_description description("Allowed options:");
    description.add_options()
        ("help", "shows this message")
        ("video_processing", "process video file")
        ("input", boost::program_options::value<std::string>(), "provides an input parameter");
    return description;
}

void printHelp(const boost::program_options::options_description& desc)
{
    std::cout << desc << std::endl;
    std::cout << std::endl;
    std::cout << "If you like to process already collected movie, please use: " << std::endl << "/Autonomous_vehicle --video_processing --input [filename]";
}

std::unique_ptr<Component> createVideoProcessingComponent(const boost::program_options::variables_map& vm)
{
    if (not vm.contains("input")) throw ParsingError();

    return createVideoProcessingComponent(vm["input"].as<std::string>());
}

std::vector<std::unique_ptr<Component>> createComponentsBasedOnParserInput(int argc, char** argv)
{
    std::vector<std::unique_ptr<Component>> componentsVector{};

    auto desc = getOptionsDescriptions();
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, getOptionsDescriptions()), vm);
    boost::program_options::notify(vm);

    try
    {
        if (vm.count("help"))
        {
            printHelp(desc);
        }
        if (vm.count("video_processing"))
        {
            componentsVector.emplace_back(createVideoProcessingComponent(vm));
        }
    }
    catch (const ParsingError& ex)
    {
        printHelp(desc);
        return {};
    }
    if (componentsVector.empty())
    {
        printHelp(desc);
    }
    return componentsVector;
}
