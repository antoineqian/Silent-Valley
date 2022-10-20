#include "gtest/gtest.h"
#include "Map.hpp"
using namespace std;

TEST(MAP, BasicAssertions)
{
    Map m({{'p', 'b'}});
    EXPECT_EQ(m.description.size(), 1);
    EXPECT_EQ(m.description[0].size(), 2);
}

TEST(MAP, WrongInput)
{
    EXPECT_THROW(Map({{'e'}}), std::invalid_argument);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}