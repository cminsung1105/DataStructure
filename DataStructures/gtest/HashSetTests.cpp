/*


#include <string>
#include <gtest/gtest.h>
#include "HashSet.hpp"


namespace
{
    template <typename T>
    unsigned int zeroHash(T t)
    {
        return 0;
    }
}


TEST(HashSet_SanityCheckTests, canCopyConstructToCompatibleType)
{

    HashSet<std::string> s1{zeroHash<std::string>};
    HashSet<std::string> s2{zeroHash<std::string>};


    HashSet<std::string> s1Copy{s1};
    HashSet<std::string> s2Copy{s2};
}


TEST(HashSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s1Copy{std::move(s1)};
    HashSet<std::string> s2Copy{std::move(s2)};
}


TEST(HashSet_SanityCheckTests, canAssignToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s3{zeroHash<int>};
    HashSet<std::string> s4{zeroHash<std::string>};

    s1 = s3;
    s2 = s4;
}


TEST(HashSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    HashSet<int> s1{zeroHash<int>};
    HashSet<std::string> s2{zeroHash<std::string>};

    HashSet<int> s3{zeroHash<int>};
    HashSet<std::string> s4{zeroHash<std::string>};

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(HashSet_SanityCheckTests, isImplemented)
{
    HashSet<int> s1{zeroHash<int>};
    EXPECT_TRUE(s1.isImplemented());

    HashSet<std::string> s2{zeroHash<std::string>};
    EXPECT_TRUE(s2.isImplemented());
}


TEST(HashSet_SanityCheckTests, containsElementsAfterAdding)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
}


TEST(HashSet_SanityCheckTests, doesNotContainElementsNotAdded)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_FALSE(s1.contains(21));
    EXPECT_FALSE(s1.contains(2));
    EXPECT_FALSE(s1.contains(9));
}


TEST(HashSet_SanityCheckTests, sizeIsNumberOfElementsAdded)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(3, s1.size());
}


TEST(HashSet_SanityCheckTests, elementsAtIndexAccordingToHash)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(3, s1.elementsAtIndex(0));
    EXPECT_EQ(0, s1.elementsAtIndex(1));

    EXPECT_TRUE(s1.isElementAtIndex(11, 0));
    EXPECT_TRUE(s1.isElementAtIndex(1, 0));
    EXPECT_TRUE(s1.isElementAtIndex(5, 0));

    EXPECT_FALSE(s1.isElementAtIndex(11, 1));
    EXPECT_FALSE(s1.isElementAtIndex(1, 1));
    EXPECT_FALSE(s1.isElementAtIndex(5, 1));
}
*/