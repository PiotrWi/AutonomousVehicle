#include "SysHelper.hpp"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

void SysfsHelper::writeToSys(const char* loc, const std::string & value)
{
    auto fd = openToWrite(loc);
    writeToSys(fd, value);
}

FDRaiiWrapper SysfsHelper::openToWrite(const char* loc)
{
    FDRaiiWrapper fd(open(loc, O_WRONLY), [](int fd){ close(fd); } );
    if (fd.get() <= 0)
    {
        perror("openToWrite return error: ");
        std::cerr << "openToWrite args: " << loc << std::endl;
    }
    return fd;
}

void SysfsHelper::writeToSys(FDRaiiWrapper& fd, const std::string & value)
{
    auto ret = write(fd.get(), value.c_str(), value.size());
    if (ret < 0)
    {
        perror("writeToSys:  return error");
        std::cerr << "writeToSys args: " << fd.get() << " " << value << std::endl;
    }
}
