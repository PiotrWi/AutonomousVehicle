#pragma once

#include <QImage>

namespace utils
{

class DumpImages
{
public:
    explicit DumpImages(const char* location, const char* prefix);
    void dump(QImage &image) const;
private:
    std::string directory_;
    const char *prefix_;
};

}  // namespace utils
