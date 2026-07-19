#include "Piece.hpp"
#include "Board.hpp"
namespace chess {

std::string Pawn::getSymbol() const {
    if(m_color==Color::White){
        return "P";
    }
        return "p";
}

std::vector<Move> Pawn::getValidMoves(const Board& board, const Position& from) const {
    return {};
}
std::string Knight::getSymbol() const {
    return (m_color == Color::White) ? "N" : "n";
}

std::vector<Move> Knight::getValidMoves(const Board& board, const Position& from) const {
    return {};
}

std::string Bishop::getSymbol() const {
    return (m_color == Color::White) ? "B" : "b";
}

std::vector<Move> Bishop::getValidMoves(const Board& board, const Position& from) const {
    return {};
}

std::string Rook::getSymbol() const {
    return (m_color == Color::White) ? "R" : "r";
}

std::vector<Move> Rook::getValidMoves(const Board& board, const Position& from) const {
    return {};
}


std::string Queen::getSymbol() const {
    return (m_color == Color::White) ? "Q" : "q";
}

std::vector<Move> Queen::getValidMoves(const Board& board, const Position& from) const {
    return {};
}


std::string King::getSymbol() const {
    return (m_color == Color::White) ? "K" : "k";
}

std::vector<Move> King::getValidMoves(const Board& board, const Position& from) const {
    return {};
  }
}