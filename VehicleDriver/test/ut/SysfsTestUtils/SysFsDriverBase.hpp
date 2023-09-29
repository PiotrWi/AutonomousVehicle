#pragma once

#include <gtest/gtest.h>
#include "Journal.hpp"
#include "SequenceVerifier.hpp"

class SysFsDriverBase : public ::testing::Test
{
public:
    void SetUp() override
    {
        Journal::getInstance().clear();
    }
    void verify()
    {
        auto sv = SequenceVerified(Journal::getInstance().getEntries());
        for (auto&& expectation: expectationsVector_)
        {
            ASSERT_TRUE(sv.verify(expectation));
        }
    }
protected:
    std::vector<std::vector <std::string>> expectationsVector_;
};
