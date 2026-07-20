#pragma once
#include "Position.hpp"
#include "Piece.hpp"
#include <memory>
#include <array>

namespace chess{
    class Board{
        private:
        std::array<std::array<std::unique_ptr<Piece>, 8>, 8> m_grid;
        public:
        Board();
        void setupInitialBoard();
        const Piece* getPieceAt(const Position& pos) const;
        Piece* getPieceAt(const Position& pos);
        void setPieceAt(const Position& pos,std::unique_ptr<Piece> piece);
        std::unique_ptr<Piece> removePieceAt(const Position& pos);
        void movePiece(const Position& from,const Position& to);
        void print() const;
        void clear();
    };
}