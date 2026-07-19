#include "Board.hpp"
#include "Game.hpp"
#include <iostream>

int main() {
    chess::Board board;
    board.setupInitialBoard();
    board.print();

    chess::Position knightPos{0, 1};
    const chess::Piece* knight = board.getPieceAt(knightPos);
    auto moves = knight->getValidMoves(board, knightPos);
    std::cout << "b1 Knight'in hamle sayisi: " << moves.size() << "\n";
    for (const auto& m : moves) {
        std::cout << "  -> (" << m.to.row << ", " << m.to.col << ")\n";
    }

    std::cout << "\n--- Game testi ---\n";
    chess::Game game;
    game.makeMove(chess::Move{{1, 4}, {3, 4}});
    game.getBoard().print();
    std::cout << "Sira kimde: "
              << (game.getActiveColor() == chess::Color::White ? "Beyaz" : "Siyah")
              << "\n";

    std::cout << "\n--- Gecersiz hamle testi ---\n";
    game.makeMove(chess::Move{{6, 0}, {5, 0}});
    game.getBoard().print();
    std::cout << "Sira kimde: "
              << (game.getActiveColor() == chess::Color::White ? "Beyaz" : "Siyah")
              << "\n";

    return 0;
}