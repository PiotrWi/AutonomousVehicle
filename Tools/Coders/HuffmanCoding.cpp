#include "HuffmanCoding.hpp"
#include <array>
#include <span>
#include <algorithm>
#include <ranges>

#include "detail/heap.hpp"

namespace tools::coders
{

namespace
{

struct HuffmanTreeNode
{
    unsigned char codedSymbol_;
    unsigned long freq_ = 0;
    HuffmanTreeNode *zeroChild = nullptr;
    HuffmanTreeNode *oneChild = nullptr;
};

using HuffmanNodes = std::array<HuffmanTreeNode, ElementsToCode>;

using HuffmanTreeNodes = std::vector<HuffmanTreeNode>;
class HuffmanTree
{
public:
    explicit HuffmanTree(std::size_t expectedSize)
    {
        nodes_.resize(expectedSize);
        pushPosition_ = nodes_.size();
    }
    HuffmanTreeNode* push(HuffmanTreeNode node)
    {
        nodes_[--pushPosition_] = node;
        return &nodes_[pushPosition_];
    }
    const HuffmanTreeNodes& get()
    {
        return nodes_;
    };
private:
    unsigned int pushPosition_;
    HuffmanTreeNodes nodes_;
};

auto initNodes(HuffmanNodes& nodes)
{
    unsigned char i = 0;
    for (auto& elem : std::span(nodes.begin(), nodes.begin()+ElementsToCode))
    {
        elem.codedSymbol_ = i++;
    }
}

auto calculateFrequency(const std::vector<unsigned char>& payload, HuffmanNodes& occurrences)
{
    for (auto c : payload)
    {
        ++occurrences[c].freq_;
    }
}

template <typename TComp>
auto initHuffmanNodesHeap(const std::vector<unsigned char>& payload, TComp comp)
{
    HuffmanNodes nodes;
    initNodes(nodes);
    calculateFrequency(payload, nodes);
    auto nodesWithNotZeroFreq = nodes | std::views::filter([](auto&& elem) { return elem.freq_ > 0; });

    auto heap = detail::Heap<HuffmanTreeNode, decltype(comp)>(nodesWithNotZeroFreq.begin(), nodesWithNotZeroFreq.end(), comp);
    return heap;
}

template <typename THeap>
auto buildHuffmanNodesTree(THeap& heap)
{
    HuffmanTree tree(heap.size() * 2 - 1);
    while (heap.size() > 1)
    {
        auto zeroNode = heap.pop();
        auto oneNode = heap.pop();

        HuffmanTreeNode aggregatedNode;
        aggregatedNode.freq_ = zeroNode.freq_ + oneNode.freq_;
        aggregatedNode.zeroChild = tree.push(zeroNode);
        aggregatedNode.oneChild = tree.push(oneNode);

        heap.push(aggregatedNode);
    }
    tree.push(heap.pop());
    return tree;
}

bool isLeaf(const HuffmanTreeNode &node)
{
    return node.zeroChild == nullptr && node.oneChild == nullptr;
}

auto visit(const HuffmanTreeNode& node, std::array<CodeElement, ElementsToCode>& table, CodeElement codeElement)
{
    if (isLeaf(node))
    {
        table[node.codedSymbol_] = codeElement;
        return;
    }
    CodeElement zero = CodeElement(codeElement.len + 1u, codeElement.mask);
    visit(*node.zeroChild, table, zero);
    CodeElement one = CodeElement(codeElement.len + 1u, codeElement.mask | (1u << codeElement.len));
    visit(*node.oneChild, table, one);
}

auto createCharToCode(HuffmanTree& tree)
{
    std::array<CodeElement, ElementsToCode> codeTable;
    auto treeElements = tree.get();
    if (isLeaf(treeElements[0]))
    {
        codeTable[treeElements[0].codedSymbol_] = {1, 1u};
        return codeTable;
    }

    visit(treeElements[0], codeTable, {});
    return codeTable;
}

}  // namespace

std::tuple<TPayloadLength, TcodingTable, TCodedStr> encode(const std::vector<unsigned char>& payload)
{
    std::vector<unsigned char> encodedStr;

    auto heapComp = +[](const HuffmanTreeNode& lhs, const HuffmanTreeNode& rhs) { return lhs.freq_ > rhs.freq_; };
    auto heap = initHuffmanNodesHeap(payload, heapComp);
    HuffmanTree tree = buildHuffmanNodesTree(heap);

    auto charToCode = createCharToCode(tree);

    unsigned char cursor = 0;
    unsigned char codedChar = 0u;
    for (auto c : payload)
    {
        auto codeElement = charToCode[c];
        auto bytesToCode = codeElement.len;
        auto maskToCode = codeElement.mask;

        while (bytesToCode)
        {
            unsigned char elementsLeftInCodedChar = 8 - cursor;
            auto bytesToCodeInThisIteration = std::min(elementsLeftInCodedChar, bytesToCode);

            auto maskToCodeInThisIteration = maskToCode & ((1u << elementsLeftInCodedChar) - 1);
            codedChar |= maskToCodeInThisIteration << cursor;
            maskToCode = maskToCode >> elementsLeftInCodedChar;
            bytesToCode -= bytesToCodeInThisIteration;
            cursor += bytesToCodeInThisIteration;

            if (cursor == 8)
            {
                encodedStr.emplace_back(codedChar);
                cursor = 0;
                codedChar = 0u;
            }
        }
    }
    if (cursor != 0)
    {
        encodedStr.emplace_back(codedChar);
    }

    return std::make_tuple(payload.size(), charToCode, encodedStr);
}



}  // namespace tools::coders
