#pragma once

#include <string>
#include <vector>
#include <optional>

void replaceAll(std::string& inOut, const std::string& pattern, const std::string& value);
void instantiate(std::vector<std::string>& inout, const std::string& pattern, const std::string& value);

class SequenceVerified
{
public:
    SequenceVerified(const std::vector<std::string>& allJournalEntities);
    bool verify (std::vector<std::string> sequence);
private:
    bool containsInputPattern(const std::string& line);
    std::optional<std::vector<std::pair<std::string, std::string>>> matchSpecial(const std::string& line,
        std::string& patternLine);

    std::vector<std::string> journalEntities_;
};
