#include "Board.hpp"
#include <iostream>

namespace chess{
    Board::Board(){
        int r,c;
        for(r=0;r<8;++r){
            for(c=0;c<8;++c){
                m_grid[r][c]=nullptr;
            }
        }        
    }
    void Board:: setupInitialBoard(){
        int r,c;
        for(r=0;r<8;++r){
            for(c=0;c<8;++c){
                m_grid[r][c]=nullptr;
            }
        } 
        for (int c = 0; c < 8; ++c) {
        m_grid[1][c] = std::make_unique<Pawn>(Color::White);
            }
        m_grid[0][0] = std::make_unique<Rook>(Color::White);
        m_grid[0][7] = std::make_unique<Rook>(Color::White);
        m_grid[0][1] = std::make_unique<Knight>(Color::White);
        m_grid[0][6] = std::make_unique<Knight>(Color::White);
        m_grid[0][2] = std::make_unique<Bishop>(Color::White);
        m_grid[0][5] = std::make_unique<Bishop>(Color::White);
        m_grid[0][3] = std::make_unique<Queen>(Color::White);
        m_grid[0][4] = std::make_unique<King>(Color::White);
        for (int c = 0; c < 8; ++c) {
            m_grid[6][c] = std::make_unique<Pawn>(Color::Black);
        }
        m_grid[7][0] = std::make_unique<Rook>(Color::Black);
        m_grid[7][7] = std::make_unique<Rook>(Color::Black);
        m_grid[7][1] = std::make_unique<Knight>(Color::Black);
        m_grid[7][6] = std::make_unique<Knight>(Color::Black);
        m_grid[7][2] = std::make_unique<Bishop>(Color::Black);
        m_grid[7][5] = std::make_unique<Bishop>(Color::Black);
        m_grid[7][3] = std::make_unique<Queen>(Color::Black);
        m_grid[7][4] = std::make_unique<King>(Color::Black);
    }


    const Piece* Board::getPieceAt(const Position& pos)const{
        if(!pos.isValid()){
            return nullptr;
        }
        return m_grid[pos.row][pos.col].get();
    }
    Piece* Board::getPieceAt(const Position& pos){
        if(!pos.isValid()){
            return nullptr;
        }
        return m_grid[pos.row][pos.col].get();
    }
    void Board:: setPieceAt(const Position& pos,std::unique_ptr<Piece> piece){
        if(pos.isValid()){
            m_grid[pos.row][pos.col]=std::move(piece);
        }
    }

    std::unique_ptr<Piece> Board::removePieceAt(const Position& pos){
        if(pos.isValid()){
            return std::move(m_grid[pos.row][pos.col]);
        }
        return nullptr;
    }
    void Board:: movePiece(const Position& from,const Position& to){
        if(!from.isValid() || !to.isValid()){
            return ;
        }
        m_grid[to.row][to.col]=std::move(m_grid[from.row][from.col]);
    }
    void Board::print() const {
        std::cout << "\n  +---+---+---+---+---+---+---+---+\n";
        for (int r = 7; r >= 0; --r) { 
        std::cout << (r + 1) << " |"; 
        for (int c = 0; c < 8; ++c) {
            const Piece* piece = getPieceAt({r, c});
            if (piece) {
                std::cout << " " << piece->getSymbol() << " |";
            } else {
                std::cout << "   |";
            }
        }
        std::cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
        std::cout << "    a   b   c   d   e   f   g   h\n\n";
    }

}