#include "Base64.hpp"

#include <array>

namespace
{

constexpr char encodingTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

constexpr std::array<unsigned char, 255> createDecodingTable()
{
    std::array<unsigned char, 255> decTable = {};
    for (int i = 0; i < 64; ++i)
    {
        decTable[encodingTable[i]] = i;
    }
    return decTable;
}
constexpr std::array<unsigned char, 255> decodingTable = createDecodingTable();

}  // namespace

namespace tools::coders
{

std::string Base64Encode(const std::vector<unsigned char> &in)
{
    std::string out;
    unsigned int i;
    for (i = 0; i + 3 <= in.size(); i += 3) {
        unsigned char i0 = in[i + 0] & 0b00111111;
        unsigned char i1 = ((in[i + 0] & 0b11000000) >> 6) | ((in[i + 1] & 0b00001111) << 2);
        unsigned char i2 = ((in[i + 1] & 0b11110000) >> 4) | ((in[i + 2] & 0b00000011) << 4);
        unsigned char i3 = ((in[i + 2] & 0b11111100) >> 2);

        out += encodingTable[i0];
        out += encodingTable[i1];
        out += encodingTable[i2];
        out += encodingTable[i3];
    }
    // reminder
    if ((in.size() - i) == 1) {
        unsigned char i0 = in[i + 0] & 0b00111111;
        unsigned char i1 = ((in[i + 0] & 0b11000000) >> 6);
        out += encodingTable[i0];
        out += encodingTable[i1];
    }
    if ((in.size() - i) == 2) {
        unsigned char i0 = in[i + 0] & 0b00111111;
        unsigned char i1 = ((in[i + 0] & 0b11000000) >> 6) | ((in[i + 1] & 0b00001111) << 2);
        unsigned char i2 = ((in[i + 1] & 0b11110000) >> 4);
        out += encodingTable[i0];
        out += encodingTable[i1];
        out += encodingTable[i2];
    }
    return out;
}

std::vector<unsigned char> Base64Decode(const std::string &in)
{
    std::vector<unsigned char> out;
    unsigned int i;
    for (i = 0; i + 4 <= in.size(); i += 4) {
        auto c0 = decodingTable[in[i + 0]];
        auto c1 = decodingTable[in[i + 1]];
        auto c2 = decodingTable[in[i + 2]];
        auto c3 = decodingTable[in[i + 3]];

        auto i0 = c0 | ((c1 & 0b00000011) << 6);
        auto i1 = ((c1 & 0b00111100) >> 2) | ((c2 & 0b00001111) << 4);
        auto i2 = ((c2 & 0b00110000) >> 4) | ((c3 & 0b00111111) << 2);

        out.push_back(i0);
        out.push_back(i1);
        out.push_back(i2);
    }
    // reminder
    if (in.size() - i == 2)  // One byte more in original source
    {
        auto c0 = decodingTable[in[i + 0]];
        auto c1 = decodingTable[in[i + 1]];
        auto i0 = c0 | ((c1 & 0b00000011) << 6);

        out.push_back(i0);
    }
    if (in.size() - i == 3)  // One byte more in original source
    {
        auto c0 = decodingTable[in[i + 0]];
        auto c1 = decodingTable[in[i + 1]];
        auto c2 = decodingTable[in[i + 2]];

        auto i0 = c0 | ((c1 & 0b00000011) << 6);
        auto i1 = ((c1 & 0b00111100) >> 2) | ((c2 & 0b00001111) << 4);

        out.push_back(i0);
        out.push_back(i1);
    }
    return out;
}

}  // namespace tools::coders
