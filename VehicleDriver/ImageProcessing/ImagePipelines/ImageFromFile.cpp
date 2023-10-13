#include "ImageFromFile.hpp"

#include <iostream>

namespace image_processing
{

ImageFromFile::ImageFromFile(std::string filename)
    : filename_(filename)
{
}

void ImageFromFile::init()
{
}

void ImageFromFile::execute()
{
    image_ = cv::imread(filename_);
    if (image_.empty())
    {
        std::cerr << "Image read unsucessfull" << std::endl;
    }
}

std::string ImageFromFile::getDefaultName() const
{
    return {"ImageFromFile"};
}

std::any ImageFromFile::get(int outputPort)
{
    return {&image_};
}
}  // namespace image_processing
