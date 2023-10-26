#include "SysHelper.hpp"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

FDRaiiWrapper SysfsHelper::openToRead(const char *loc)
{
    FDRaiiWrapper fd(open(loc, O_RDONLY), [](int fd){ close(fd); } );
    if (fd.get() <= 0)
    {
        perror("openToRead return error: ");
        std::cerr << "openToRead args: " << loc << std::endl;
    }
    return fd;
}

std::string SysfsHelper::readFromSys(FDRaiiWrapper& fd)
{
    char buf[80];
    auto ret = read(fd.get(), buf, 10);
    if (ret < 0)
    {
        perror("writeToSys:  return error");
        std::cerr << "read args: " << fd.get() << std::endl;
    }
    return std::string(buf, ret);
}

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

FDRaiiWrapper SysfsHelper::openToRW(const char *loc)
{
    FDRaiiWrapper fd(open(loc, O_RDWR), [](int fd){ close(fd); } );
    if (fd.get() <= 0)
    {
        perror("openToRead return error: ");
        std::cerr << "openToRead args: " << loc << std::endl;
    }
    return fd;
}
