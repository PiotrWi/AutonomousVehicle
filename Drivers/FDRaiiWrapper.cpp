#include "FDRaiiWrapper.hpp"

#include <utility>

FDRaiiWrapper::FDRaiiWrapper()
        : fd_(0)
        , deleter_(nullptr)
{
}

FDRaiiWrapper::FDRaiiWrapper(int fd, void(*deleter)(int))
        : fd_(fd)
        , deleter_(deleter)
{
}

void FDRaiiWrapper::conditionallyClose()
{
    if (deleter_ && fd_ > 0)
    {
        deleter_(fd_);
    }
    fd_ = 0;
}

FDRaiiWrapper::FDRaiiWrapper(FDRaiiWrapper&& other)
{
    conditionallyClose();
    std::swap(this->fd_, other.fd_);
    std::swap(this->deleter_, other.deleter_);
}

FDRaiiWrapper& FDRaiiWrapper::operator=(FDRaiiWrapper&& other)
{
    if (this == &other)
    {
        return *this;
    }
    conditionallyClose();
    std::swap(this->fd_, other.fd_);
    std::swap(this->deleter_, other.deleter_);
    return *this;
}

FDRaiiWrapper::~FDRaiiWrapper()
{
    conditionallyClose();
}

int FDRaiiWrapper::get()
{
    return fd_;
}