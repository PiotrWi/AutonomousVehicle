#include <array>
#include <vector>

#pragma once

namespace tools::coders
{

struct CodeElement
{
    unsigned char len = 0;
    unsigned int mask = 0;
};
constexpr std::size_t ElementsToCode = 256;

using TPayloadLength = unsigned int;
using TcodingTable = std::array<CodeElement, ElementsToCode>;
using TCodedStr = std::vector<unsigned char>;

std::tuple<TPayloadLength, TcodingTable, TCodedStr> encode(
        const std::vector<unsigned char>& payload);

std::vector<unsigned char> decode(const std::vector<unsigned char>& cipher,
                                  const TcodingTable&,
                                  TPayloadLength);

}  // namespace tools::coders
