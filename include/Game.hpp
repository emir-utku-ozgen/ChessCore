#pragma once
#include "Board.hpp"
#include "Move.hpp"
#include <vector>

namespace chess{
    class Game{
        private:
        Board m_board;
        Color m_activeColor;
        std::vector<Move> m_moveHistory;
        public:
        Game();
        const Board& getBoard() const {return m_board;}
        Board& getBoard(){return m_board;}

        Color getActiveColor() const{return m_activeColor;}
        const std::vector<Move>& getMoveHistory() const{
            return m_moveHistory;
        }
        void makeMove(const Move& m);
        bool isInCheck(Color color) const;
        void switchTurn();
    };
}