#include "Board.hpp"

int main() {
    chess::Board board;
    board.setupInitialBoard();
    board.print();
    return 0;
}