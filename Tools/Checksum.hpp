#pragma once

#include <iostream>
#include <string>
#include <sstream>

template <typename TIter, typename TEndTag>
unsigned int calculateChecksum(TIter begin, TEndTag end)
{
    unsigned int out = 0;
    for (auto it = begin; it != end; ++it)
    {
        out += *it;
    }
    out = out % 1000;
    return out;
}

inline bool checkPayloadChecksum(const std::string& in)
{
    auto pos = in.find("CRC:");
    std::stringstream ss(in);
    ss.seekg(pos + 5);

    unsigned int checksumInMessage = 0;
    ss >> checksumInMessage;

    pos = in.find("PAYLOAD:");
    auto payload = in.substr(pos + 9, std::string::npos);
    auto payloadEnd = payload.end();
    if (in.ends_with('\n'))
    {
        --payloadEnd;
    }
    auto checksumCalculatedFromPayload = calculateChecksum(payload.begin(), payloadEnd);
    return checksumCalculatedFromPayload == checksumInMessage;
}

namespace debug
{

inline void verifyChecksum(const std::string& in, const char* fcnName)
{
#ifdef ASSERTSON
    if (not checkPayloadChecksum(in))
    {
        std::cout << "Checksum is incorrect in: fcnName" << std::endl;
    }
#endif
}
#define VERIFY_CHECKSUM(in) debug::verifyChecksum(in, __FUNCTION__)

}  // namespace debug
