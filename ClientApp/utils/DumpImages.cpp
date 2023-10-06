#include "DumpImages.hpp"

#include <iostream>
#include <filesystem>

#include <QImage>

#include <Tools/CurrentTime.hpp>

namespace utils
{

DumpImages::DumpImages(const char *location, const char *prefix)
    : prefix_(prefix)
{
    auto currentTimeStr = getCurrentTime();
    std::filesystem::path dir(location);
    dir += currentTimeStr;
    std::filesystem::create_directories(dir);
    directory_ = dir.string();
}

void DumpImages::dump(QImage &image) const
{
    static int i = 0;

    auto path = QString::fromStdString(directory_) + "/" + prefix_ + "_" + QString::number(++i);
    auto success = image.save(path, "PNG");
    if (not success)
    {
        std::cout << "Failed to write image to file: " << path.toStdString() << std::endl;
    }
}



}  // namespace utils
