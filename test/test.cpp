#include "gtest/gtest.h"
#include "Map.hpp"
using namespace std;

TEST(MAP, BasicAssertions)
{
    vector<vector<char>> description = {{'p', 'b'}};
    Map m(description);
    EXPECT_EQ(m.description.size(), 1);
    EXPECT_EQ(m.description[0].size(), 2);

    Map m2("../../test/mapDesc.txt");
    EXPECT_EQ(m2.description.size(), 2);
    EXPECT_EQ(m2.description[0].size(), 2);
}

TEST(MAP, WrongInput)
{
    vector<vector<char>> description = {{'e', 'b'}};

    EXPECT_THROW(Map{description}, std::invalid_argument);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}