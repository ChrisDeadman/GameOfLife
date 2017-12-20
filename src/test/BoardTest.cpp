#include "Board.h"

#include "gtest/gtest.h"

TEST(Board, AliveNeighborsCaseTopLeft) {
    const int row = 0;
    const int column = 0;

    Board board(3, 3);
    int expected = 0;

    // Top Left cell
    board.setCellState(row, column, alive);
    EXPECT_EQ(0, board.getAliveNeighbors(row, column));

    // Neighbors
    //
    //board.setCellState(0, 0, alive);
    //EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 0, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 1, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));
}

TEST(Board, AliveNeighborsCaseTopRight) {
    const int row = 0;
    const int column = 2;

    Board board(3, 3);
    int expected = 0;

    // Top Left cell
    board.setCellState(row, column, alive);
    EXPECT_EQ(0, board.getAliveNeighbors(row, column));

    // Neighbors
    //
    board.setCellState(0, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    //board.setCellState(0, 2, alive);
    //EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 2, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 1, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));
}

TEST(Board, AliveNeighborsCaseCenter) {
    const int row = 1;
    const int column = 1;

    Board board(3, 3);
    int expected = 0;

    // Top Left cell
    board.setCellState(row, column, alive);
    EXPECT_EQ(0, board.getAliveNeighbors(row, column));

    // Neighbors
    //
    board.setCellState(0, 0, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 2, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 0, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    //board.setCellState(1, 1, alive);
    //EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 2, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 0, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 2, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));
}

TEST(Board, AliveNeighborsCaseBottomLeft) {
    const int row = 2;
    const int column = 0;

    Board board(3, 3);
    int expected = 0;

    // Top Left cell
    board.setCellState(row, column, alive);
    EXPECT_EQ(0, board.getAliveNeighbors(row, column));

    // Neighbors
    //
    board.setCellState(0, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 1, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 0, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    //board.setCellState(2, 0, alive);
    //EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));
}

TEST(Board, AliveNeighborsCaseBottomRight) {
    const int row = 2;
    const int column = 2;

    Board board(3, 3);
    int expected = 0;

    // Top Left cell
    board.setCellState(row, column, alive);
    EXPECT_EQ(0, board.getAliveNeighbors(row, column));

    // Neighbors
    //
    board.setCellState(0, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 1, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(0, 2, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(1, 2, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 0, alive);
    EXPECT_EQ(expected, board.getAliveNeighbors(row, column));

    board.setCellState(2, 1, alive);
    EXPECT_EQ(++expected, board.getAliveNeighbors(row, column));

    //board.setCellState(2, 2, alive);
    //EXPECT_EQ(expected, board.getAliveNeighbors(row, column));
}
