#include "gtest/gtest.h"
#include <iostream>
using namespace std;

TEST(MAP, BasicAssertions)
{
    EXPECT_EQ(6 * 6, 36);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}