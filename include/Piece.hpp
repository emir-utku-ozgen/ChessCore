#pragma once
#include "Move.hpp"  
#include "Position.hpp"
#include <string>
#include <vector>

namespace chess{
    enum class Color{
        White,
        Black
    };

    class Board;
    struct Move;
    class Piece{
        protected:
        Color m_color;
        public:
        Piece(Color color):m_color(color){}
        virtual ~Piece()=default;
        Color getColor() const{
            return m_color;
        }
        virtual std::string getSymbol()const=0;
        virtual std:: vector<Move> getValidMoves(const Board& board,const Position& from) const=0;
        };
        class Pawn:public Piece{
            public:
            Pawn(Color color):Piece(color){}
            std::string getSymbol()const override;
            std::vector<Move> getValidMoves(const Board& board,const Position& from) const override;
        };
        class Knight: public Piece{
            public:
            Knight(Color color):Piece(color){}
            std::string getSymbol()const override;
            std:: vector<Move> getValidMoves(const Board& board,const Position& from) const override;
        };
        class Bishop : public Piece {
            public:
            Bishop(Color color) : Piece(color) {}
            std::string getSymbol() const override;
            std::vector<Move> getValidMoves(const Board& board, const Position& from) const override;
        };
        class Rook : public Piece {
        public:
        Rook(Color color) : Piece(color) {}
        std::string getSymbol() const override;
        std::vector<Move> getValidMoves(const Board& board, const Position& from) const override;
        };
        class Queen : public Piece {
        public:
        Queen(Color color) : Piece(color) {}
        std::string getSymbol() const override;
        std::vector<Move> getValidMoves(const Board& board, const Position& from) const override;
        };
        class King : public Piece {
        public:
        King(Color color) : Piece(color) {}
        std::string getSymbol() const override;
        std::vector<Move> getValidMoves(const Board& board, const Position& from) const override;
        };
}