#include "SequenceVerifier.hpp"

void replaceAll(std::string& inOut, const std::string& pattern, const std::string& value)
{
    std::string::size_type pos;
    while (pos = inOut.find(pattern), pos != std::string::npos)
    {
        inOut.replace(pos, pattern.size(), value);
    }
}

void instantiate(std::vector<std::string>& inout, const std::string& pattern, const std::string& value)
{
    using namespace std;
    auto fullPattern = "${"s + pattern  + "}"s;
    for (auto&& line : inout)
    {
        replaceAll(line, fullPattern, value);
    }
}

SequenceVerified::SequenceVerified(const std::vector<std::string>& allJournalEntities)
    : journalEntities_(allJournalEntities) {}

bool SequenceVerified::verify (std::vector<std::string> sequence)
{
    if (sequence.empty())
    {
        return true;
    }

    auto sequenceIt = std::begin(sequence);
    for (auto journalIt = std::begin(journalEntities_); journalIt!= std::end(journalEntities_);)
    {
        auto& entity = *journalIt;
        if (containsInputPattern(*sequenceIt))
        {
            auto patternVec = matchSpecial(entity, *sequenceIt);
            if (patternVec)
            {
                for (auto&& patternToValue : *patternVec)
                {
                    instantiate(sequence, patternToValue.first, patternToValue.second);
                }
                ++sequenceIt;
                journalEntities_.erase(journalIt);
                if (sequenceIt == std::end(sequence))
                {
                    return true;
                }
                continue;
            }
        }
        else if (entity == *sequenceIt)
        {
            ++sequenceIt;
            journalEntities_.erase(journalIt);
            if (sequenceIt == std::end(sequence))
            {
                return true;
            }
            continue;
        }
        ++journalIt;
    }
    return false;
}

bool SequenceVerified::containsInputPattern(const std::string& line)
{
    return line.find("@{") != std::string::npos;
}

std::optional<std::vector<std::pair<std::string, std::string>>> SequenceVerified::matchSpecial(const std::string& line,
                                                                             std::string& patternLine)
{
    auto patternLineCpy = patternLine;
    std::string::size_type pos;
    std::vector<std::pair<std::string, std::string>> patternToValue;

    while (pos = patternLineCpy.find("@{"), pos != std::string::npos )
    {
        if (line.substr(0, pos) != patternLineCpy.substr(0, pos))
        {
            return {};
        }

        auto nextSpecialPos = patternLineCpy.find("@{", pos + 1);
        auto endOfSpecial = patternLineCpy.find("}", pos + 1);
        auto nonSpecialPartOfPattern = patternLineCpy.substr(endOfSpecial + 1, nextSpecialPos - endOfSpecial);

        auto posInGivenLine = line.find(nonSpecialPartOfPattern, pos);
        if (posInGivenLine == std::string::npos)
        {
            return {};
        }

        auto patternName = patternLineCpy.substr(pos+2, endOfSpecial - (pos+2));
        auto patternValue = line.substr(pos, posInGivenLine - pos);
        patternToValue.emplace_back(patternName, patternValue);
        replaceAll(patternLineCpy, "@{" + patternName + "}", patternValue);
    }

    if (patternLineCpy == line)
    {
        patternLine = patternLineCpy;
        return patternToValue;
    }
    return {};
}
