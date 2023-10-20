#include "HuffmanCoding.hpp"

namespace tools::coders
{

namespace
{

struct DecodingNode
{
    bool isLeaf = false;
    unsigned char nodeCharacter_ = 0;
    DecodingNode* nextNodes[2] = {nullptr, nullptr};
};

class DecodingMachine
{
public:
    explicit DecodingMachine()
    {
        top = new DecodingNode();
        top->isLeaf = false;
        currentNode = top;
    }

    void buildNode(DecodingNode* currentNode, CodeElement ce, unsigned char nodeCharacter)
    {
        --ce.len;
        unsigned char bit = 0b1 & ce.mask;
        ce.mask >>= 1;

        if (currentNode->nextNodes[bit] == nullptr)
        {
            currentNode->nextNodes[bit] = new DecodingNode();
        }
        if(ce.len == 0)
        {
            currentNode->nextNodes[bit]->nodeCharacter_ = nodeCharacter;
            currentNode->nextNodes[bit]->isLeaf = true;
        }
        else
        {
            currentNode->nextNodes[bit]->isLeaf = false;
            buildNode(currentNode->nextNodes[bit], ce, nodeCharacter);
        }
    }

    auto buildDecodingMachine(const TcodingTable & tCodingTable)
    {
        for (unsigned int i = 0; i < tCodingTable.size(); ++i)
        {
            auto codingEntity = tCodingTable[i];
            if (codingEntity.len == 0)
            {
                continue;
            }
            buildNode(top, codingEntity, i);
        }
    }

    void consumeBit(bool bit)
    {
        currentNode = currentNode->nextNodes[bit];
        if (currentNode->isLeaf)
        {
            payload.push_back(currentNode->nodeCharacter_);
            currentNode = top;
        }
    }

    std::vector<unsigned char> get(std::size_t firstBytes)
    {
        std::vector<unsigned char> v;
        std::swap(v, payload);

        v.erase(v.begin() + firstBytes, v.end());
        return v;
    }
private:
    DecodingNode* top;
    DecodingNode* currentNode;

    std::vector<unsigned char> payload;
};

auto buildDecodingMachine(const TcodingTable & tCodingTable)
{
    DecodingMachine dm_;
    dm_.buildDecodingMachine(tCodingTable);
    return dm_;
}


}  // namespace

std::vector<unsigned char> decode(const std::vector<unsigned char> &cipher,
                                          const TcodingTable &tCodingTable,
                                          TPayloadLength len)
{
    auto decodingMachine = buildDecodingMachine(tCodingTable);

    for (auto c : cipher)
    {
        for (unsigned char i = 0; i < 8; ++i)
        {
            auto bit = ((0b1 << i) & c) >> i;
            decodingMachine.consumeBit(bit);
        }
    }
    return decodingMachine.get(len);
}

}  // namespace tools::coders
