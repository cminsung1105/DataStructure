/*
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "HashSet.hpp"
#include "WordChecker.hpp"

namespace
{
    template <typename T>
    unsigned int zeroHash(const T& t)
    {
        return 0;
    }
}

TEST(WordChecker_SanityCheckTests, canCreateWithSetOfStrings)
{
    WordChecker w{HashSet<std::string>{zeroHash<std::string>}};
}


TEST(WordChecker_SanityCheckTests, wordsExistWhenInSet)
{
    HashSet<std::string> set{zeroHash<std::string>};
    set.add("HELLO");
    set.add("THERE");
    set.add("BOO");

    WordChecker checker{set};

    EXPECT_TRUE(checker.wordExists("HELLO"));
    EXPECT_TRUE(checker.wordExists("THERE"));
    EXPECT_TRUE(checker.wordExists("BOO"));
}


TEST(WordChecker_SanityCheckTests, wordsDoNotExistWhenNotInSet)
{
    HashSet<std::string> set{zeroHash<std::string>};
    set.add("HELLO");
    set.add("THERE");
    set.add("BOO");

    WordChecker checker{set};

    EXPECT_FALSE(checker.wordExists("NOTBOO"));
    EXPECT_FALSE(checker.wordExists("HELLOTHERE"));
}


TEST(WordChecker_SanityCheckTests, canGenerateSuggestions)
{
    HashSet<std::string> set{zeroHash<std::string>};
    set.add("ABDC");
    set.add("ZZZZZ");

    WordChecker checker{set};

    std::vector<std::string> suggestions = checker.findSuggestions("ABCD");

    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABDC", suggestions[0]);
}
*/