#include "../src/controllers/rushHour.h"
#include <gtest/gtest.h>

TEST(RushHourTest, IsSolved) {

    std::vector<std::vector<char>> board = {
        {'.','.','A','A','.','.'},
        {'.','X','X','.','B','.'},
        {'.','.','.','.','B','.'},
        {'.','D','C','C','C','.'},
        {'.','D','.','.','.','.'},
        {'.','E','E','.','.','.'}
    };
    
    RushHour rushHour(board);

    ASSERT_EQ(false, rushHour.isSolved());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
