#pragma once

#include <string>
#include <vector>
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
