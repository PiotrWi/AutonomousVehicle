#include "Journal.hpp"

Journal &Journal::getInstance()
{
    static Journal j;
    return j;
}

void Journal::clear()
{
    data_.clear();
}

void Journal::addLine(std::string line)
{
    data_.emplace_back(line);
}

std::vector<std::string> Journal::getEntries()
{
    return data_;
}