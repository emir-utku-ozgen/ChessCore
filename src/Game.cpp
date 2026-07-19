#include "Game.hpp"
#include <algorithm>
namespace chess{
    Game::Game(){
        m_board.setupInitialBoard();
        m_activeColor=Color::White;
    }
    void Game::switchTurn(){
        m_activeColor=(m_activeColor==Color::White)? Color::Black: Color::White;
    }
    void Game::makeMove(const Move& m) {
    const Piece* piece = m_board.getPieceAt(m.from);
    if (piece == nullptr) {
        return;
    }
    if (piece->getColor() != m_activeColor) {
        return;
    }

    std::vector<Move> validMoves = piece->getValidMoves(m_board, m.from);
    auto it = std::find(validMoves.begin(), validMoves.end(), m);
    
    if (it != validMoves.end()) {
       
        std::unique_ptr<Piece> captured = m_board.removePieceAt(m.to);
        
        
        m_board.movePiece(m.from, m.to);
        
        bool selfCheck = isInCheck(m_activeColor);
        
        if (selfCheck) {

            m_board.movePiece(m.to, m.from); 
            if (captured != nullptr) {
                m_board.setPieceAt(m.to, std::move(captured));
            }
            return; 
        } else {
            m_moveHistory.push_back(m);
            switchTurn();
        }
    }
}
    bool Game::isInCheck(Color color) const {
        Position kingPos{-1, -1};
        bool kingFound = false;

        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                Position currentPos{r, c};
                const Piece* piece = m_board.getPieceAt(currentPos);
                
                if (piece != nullptr && piece->getColor() == color) {
                    const King* king = dynamic_cast<const King*>(piece);
                    if (king != nullptr) {
                        kingPos = currentPos;
                        kingFound = true;
                        break;
                    }
                }
            }
            if (kingFound) break;
        }

        if (!kingFound) return false;

        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                Position currentPos{r, c};
                const Piece* enemyPiece = m_board.getPieceAt(currentPos);
                
                if (enemyPiece != nullptr && enemyPiece->getColor() != color) {
                    std::vector<Move> enemyMoves = enemyPiece->getValidMoves(m_board, currentPos);
                    for (const auto& enemyMove : enemyMoves) {
                        if (enemyMove.to == kingPos) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }
}