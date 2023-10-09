#include "DumpImage.hpp"

#include <filesystem>
#include <string>

#include <Tools/CurrentTime.hpp>

namespace image_processing
{

using namespace std;

DumpImage::DumpImage(std::string localization, const char *prefix)
    : localization_(localization)
    , prefix_(prefix)
{
}

void DumpImage::init()
{
    std::filesystem::path givenPath(localization_);
    givenPath += getCurrentTime();
    std::filesystem::create_directories(givenPath);
    dirrectory_ = givenPath.string();
}

void DumpImage::execute(cv::Mat &image)
{
    static int i = 0;
    std::string path = dirrectory_ + "/"s + prefix_ + "_"s + std::to_string(++i) + ".png"s;
    cv::imwrite(path, image);
}

} // image_processing
