#pragma once

namespace tools::coders::detail
{

template <typename TNode, typename TComp>
class Heap
{
public:
    template<class TIter>
    explicit Heap(TIter begin, TIter end, TComp& comp) : comp_(comp)
    {
        std::copy(begin, end, std::back_inserter(nodes_));
        std::make_heap(nodes_.begin(), nodes_.end(), comp);
    }

    [[nodiscard]] std::size_t size() const
    {
        return nodes_.size();
    }

    TNode pop()
    {
        auto node = *nodes_.begin();
        std::pop_heap(nodes_.begin(), nodes_.end(), comp_);
        nodes_.pop_back();
        return node;
    }

    void push(TNode node)
    {
        nodes_.push_back(node);
        std::push_heap(nodes_.begin(), nodes_.end(), comp_);
    }
private:
    TComp comp_;
    std::vector<TNode> nodes_;
};

}  // namespace tools::coders::detail
