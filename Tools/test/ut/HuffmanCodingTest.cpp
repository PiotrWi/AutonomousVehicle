#include <Tools/Coders/HuffmanCoding.hpp>
#include <Tools/Coders/detail/heap.hpp>

#include <gtest/gtest.h>

using namespace tools::coders;

TEST(HeapShall, beBuildFromVec)
{
    std::vector<unsigned char> toAdd{9, 2, 31, 43, 1};
    auto comparator = +[](unsigned char lhs, unsigned char rhs) { return lhs > rhs; };

    detail::Heap<unsigned char, decltype(comparator)> heap(toAdd.begin(), toAdd.end(), comparator);

    ASSERT_EQ(heap.size(), 5);
    ASSERT_EQ(heap.pop(), 1);
    ASSERT_EQ(heap.pop(), 2);
    ASSERT_EQ(heap.pop(), 9);
    ASSERT_EQ(heap.pop(), 31);
    ASSERT_EQ(heap.pop(), 43);
    ASSERT_EQ(heap.size(), 0);
}

TEST(HeapShall, correctlyPushElements)
{
    std::vector<unsigned char> toAdd{9, 2};
    auto comparator = +[](unsigned char lhs, unsigned char rhs) { return lhs > rhs; };

    detail::Heap<unsigned char, decltype(comparator)> heap(toAdd.begin(), toAdd.end(), comparator);

    heap.push(1);
    heap.push(43);
    heap.push(31);

    ASSERT_EQ(heap.size(), 5);
    ASSERT_EQ(heap.pop(), 1);
    ASSERT_EQ(heap.pop(), 2);
    ASSERT_EQ(heap.pop(), 9);
    ASSERT_EQ(heap.pop(), 31);
    ASSERT_EQ(heap.pop(), 43);
    ASSERT_EQ(heap.size(), 0);
}

TEST(HuffmanCodeShall, encodeDecodeFourChars)
{
    std::vector<unsigned char> payloadToCompress{0, 1, 2, 3};
    auto [len, codingTable, codedStr] = encode(payloadToCompress);
    auto decodedStr = decode(codedStr, codingTable, len);
    ASSERT_EQ(payloadToCompress, decodedStr);
}

TEST(HuffmanCodeShall, encodeDecodeLongTwoSymbolsPattern)
{
    std::vector<unsigned char> payloadToCompress{0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1};
    auto [len, codingTable, codedStr] = encode(payloadToCompress);
    auto decodedStr = decode(codedStr, codingTable, len);
    ASSERT_EQ(payloadToCompress, decodedStr);
}

TEST(HuffmanCodeShall, encodeDecodeLongThreeSymbolsPattern)
{
    std::vector<unsigned char> payloadToCompress{0, 1, 2, 2, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 2, 0, 0, 1, 1, 0, 1, 0, 1};
    auto [len, codingTable, codedStr] = encode(payloadToCompress);
    auto decodedStr = decode(codedStr, codingTable, len);
    ASSERT_EQ(payloadToCompress, decodedStr);
}

TEST(HuffmanCodeShall, encodeDecodeLongSixSymbolsPattern)
{
    std::vector<unsigned char> payloadToCompress{4, 0, 4, 1, 2, 5, 2, 0, 0, 1, 3, 1, 0, 5, 1, 0, 0, 1, 1, 0, 1, 0, 5, 2, 0, 0, 1, 4, 1, 0, 1, 3, 0, 1};
    auto [len, codingTable, codedStr] = encode(payloadToCompress);
    auto decodedStr = decode(codedStr, codingTable, len);
    ASSERT_EQ(payloadToCompress, decodedStr);
}

TEST(HuffmanCodeShall, encodeDecodeFullSymbolsPattern)
{
    std::vector<unsigned char> payloadToCompress;
    for (int i = 0; i < 5000; ++i)
    {
        payloadToCompress.push_back(rand()%2);
        payloadToCompress.push_back(rand()%3);
        payloadToCompress.push_back(rand()%7);
        payloadToCompress.push_back(rand()%20);
        payloadToCompress.push_back(rand()%60);
        payloadToCompress.push_back(rand()%120);
        payloadToCompress.push_back(rand()%256);
    }
    auto [len, codingTable, codedStr] = encode(payloadToCompress);
    auto decodedStr = decode(codedStr, codingTable, len);

    ASSERT_EQ(payloadToCompress, decodedStr);
}

TEST(HuffmanCodeShall, encodeDecodePartialSymbolsPattern)
{
    std::vector<unsigned char> payloadToCompress;
    for (int i = 0; i < 5000; ++i)
    {
        payloadToCompress.push_back(15 + rand()%2);
        payloadToCompress.push_back(15 + rand()%3);
        payloadToCompress.push_back(15 + rand()%7);
        payloadToCompress.push_back(15 + rand()%20);
        payloadToCompress.push_back(15 + rand()%60);
        payloadToCompress.push_back(15 + rand()%120);
    }
    auto [len, codingTable, codedStr] = encode(payloadToCompress);
    auto decodedStr = decode(codedStr, codingTable, len);

    ASSERT_EQ(payloadToCompress, decodedStr);
}