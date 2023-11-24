#include "SysHelper.hpp"

#include <iostream>
#include <unistd.h>
#include <fcntl.h>

std::string getLogPrefix(int FD)
{
    std::string s("SysfsHelper[FD=");
    s += std::to_string(FD);
    s += "]: ";
    return s;
}

FDRaiiWrapper SysfsHelper::openToRead(const char *loc)
{
    FDRaiiWrapper fd(open(loc, O_RDONLY), [](int fd){ close(fd); } );
    if (fd.get() <= 0)
    {
        perror("openToRead return error: ");
        std::cerr << "openToRead location: " << loc << std::endl;
    }
    std::cout << getLogPrefix(fd.get()) << " Successfully open to read: " << loc << std::endl;
    return fd;
}

std::string SysfsHelper::readFromSys(FDRaiiWrapper& fd)
{
    char buf[80];
    auto ret = read(fd.get(), buf, 80);
    if (ret < 0)
    {
        perror("readFromSys: return error");
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
        std::cerr << "openToWrite location: " << loc << std::endl;
    }
    std::cout << getLogPrefix(fd.get()) << " Successfully open to write: " << loc << std::endl;
    return fd;
}

void SysfsHelper::writeToSys(FDRaiiWrapper& fd, const std::string & value)
{
    auto ret = write(fd.get(), value.c_str(), value.size());
    if (ret < 0)
    {
        perror("writeToSys: return error");
        std::cerr << getLogPrefix(fd.get()) << " writeToSys args: " << value << std::endl;
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
    std::cout << getLogPrefix(fd.get()) << " Successfully open to rw: " << loc << std::endl;
    return fd;
}
