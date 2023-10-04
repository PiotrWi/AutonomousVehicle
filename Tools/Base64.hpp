#pragma once

#include <string>
#include <vector>

std::string Base64Encode(const std::vector<unsigned char>& in);
std::vector<unsigned char> Base64Decode(const std::string& in);
