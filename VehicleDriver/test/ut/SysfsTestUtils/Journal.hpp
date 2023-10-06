#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <vector>

class Journal
{
public:
    static Journal& getInstance();

    void clear();
    void addLine(const std::string& );
    std::vector<std::string> getEntries() const;
private:
    std::vector<std::string> data_;
};

class PrintToJournal {};

class JournalProxy
{
public:
    std::stringstream& getStream() { return ss_; };
    ~JournalProxy()
    {
        auto line = ss_.str();
        Journal::getInstance().addLine(line);
    }
private:
    std::stringstream ss_;
};

template <typename T>
std::unique_ptr<JournalProxy> operator << (const PrintToJournal&, T&& val)
{
    auto jp = std::make_unique<JournalProxy>() ;
    jp->getStream() << val;
    return jp;
}

template <typename T>
const std::unique_ptr<JournalProxy>& operator << (const std::unique_ptr<JournalProxy>& jp, T&& val)
{
    jp->getStream() << val;
    return jp;
}