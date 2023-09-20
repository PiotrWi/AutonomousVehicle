#include "SysHelper.hpp"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>



void SysfsHelper::writeToSys(const char* loc, const std::string & value)
{
    auto fd = open(loc, O_WRONLY);
    auto ret = write(fd, value.c_str(), value.size());
    if (ret < 0)
    {
        perror("writeToSys return error");
        std::cerr << "writeToSys: " << loc << " " << value << std::endl;
    }
    close(fd);
};

FDRaiiWrapper SysfsHelper::openToWrite(const char* loc)
{
    FDRaiiWrapper fd(open(loc, O_WRONLY), [](int fd){ close(fd); } );
    return fd;
}

void SysfsHelper::writeToSys(FDRaiiWrapper& fd, const std::string & value)
{
    auto ret = write(fd.get(), value.c_str(), value.size());
    if (ret < 0)
    {
        perror("writeToSys return error");
        std::cerr << "writeToSys: " << value;
    }
}
