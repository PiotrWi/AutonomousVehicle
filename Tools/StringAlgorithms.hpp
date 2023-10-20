#pragma once

#include <string>
#include <vector>

namespace tools
{

[[nodiscard]] std::string ltrim(const std::string& in, char c = ' ');
[[nodiscard]] std::string rtrim(const std::string& in, char c = ' ');
[[nodiscard]] std::string trim(const std::string& in, char c = ' ');

[[nodiscard]] std::vector<std::string> splitAndTrim(const std::string& in, char c);
[[nodiscard]] std::vector<std::string> splitAndTrimByStr(const std::string& in, const std::string& delimeter);

[[nodiscard]] std::vector<std::string> splitNumbersAndLetters(const std::string& in);

}  // namespace tools
