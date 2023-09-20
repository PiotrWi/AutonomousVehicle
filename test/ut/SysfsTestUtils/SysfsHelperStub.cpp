#include "Drivers/SysHelper.hpp"

#include "test/ut/SysfsTestUtils/Journal.hpp"

namespace
{

int getFd()
{
    static int fd = 1;
    return fd++;
}

}  // namespace

void SysfsHelper::writeToSys(const char* loc, const std::string & val)
{
    auto fd = openToWrite(loc);
    writeToSys(fd, val);
};

FDRaiiWrapper SysfsHelper::openToWrite(const char* loc)
{
    auto fd = getFd();
    PrintToJournal() << "open fd=" <<  fd <<", loc=" << loc;
    return FDRaiiWrapper(fd, [](int fd){ PrintToJournal() << "close fd=" << fd;});
}

void SysfsHelper::writeToSys(FDRaiiWrapper& fd, const std::string & val)
{
    PrintToJournal() << "write fd=" << fd.get() <<", val=" << val;
}
