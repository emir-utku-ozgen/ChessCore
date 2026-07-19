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
    std::vector<Move> moves;
    int direction=(this->getColor()==Color::White) ? 1:-1;
    int startRow=(this->getColor()==Color::White) ? 1:6;
    Position oneStep;
    oneStep.row=from.row+direction;
    oneStep.col=from.col;
    if(oneStep.isValid()){
        const Piece* pieceAtOneStep=board.getPieceAt(oneStep);
        if(pieceAtOneStep==nullptr){
            moves.push_back(Move{from,oneStep});
            if(from.row==startRow){
                Position twoStep;
                twoStep.row = from.row + (2 * direction);
                twoStep.col=from.col;
                if(twoStep.isValid() && board.getPieceAt(twoStep)==nullptr){
                    moves.push_back(Move{from,twoStep});
                }
            }
        }
    }
    int attack_offset[]={1,-1};
    for(int offset:attack_offset){
        Position target;
        target.row=from.row+direction;
        target.col=from.col+offset;
        if(target.isValid()){
            const Piece* targetPiece=board.getPieceAt(target);
            if(targetPiece!=nullptr && targetPiece->getColor()!=this->getColor()){
                moves.push_back(Move{from,target});
            }
        }
    }
return moves;
}
std::string Knight::getSymbol() const {
    return (m_color == Color::White) ? "N" : "n";
}

std::vector<Move> Knight::getValidMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    static const std::vector<std::pair<int, int>> offsets = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
    for (const auto& offset : offsets) {
        Position target{from.row + offset.first, from.col + offset.second};
        if (!target.isValid()) {
            continue;
        }
        const Piece* targetPiece = board.getPieceAt(target);
        if (targetPiece == nullptr || targetPiece->getColor() != this->getColor()) {
            moves.push_back(Move{from, target});
        }
    }
    return moves;
}
std::string Bishop::getSymbol() const {
    return (m_color == Color::White) ? "B" : "b";
}

std::vector<Move> Bishop::getValidMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    static const std::vector<std::pair<int, int>> directions = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    for(const auto& dir:directions){
        int step=1;
        while(true){
            Position target;
            target.row = from.row + (dir.first * step);
            target.col = from.col + (dir.second * step);
            if(!target.isValid()){
                break;
            }
            const Piece* targetPiece=board.getPieceAt(target);
            if(targetPiece==nullptr){
                moves.push_back(Move{from,target});
                step++;
            }else{
                if(targetPiece->getColor()!=this->getColor()){
                    moves.push_back(Move{from,target});
                }
                break;
            }
        }
    }
    return moves;
}

std::string Rook::getSymbol() const {
    return (m_color == Color::White) ? "R" : "r";
}

std::vector<Move> Rook::getValidMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    static const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    for(const auto& dir:directions){
        int step=1;
        while(true){
            Position target;
            target.row = from.row + (dir.first * step);
            target.col = from.col + (dir.second * step);
            if(!target.isValid()){
                break;
            }
            const Piece* targetPiece=board.getPieceAt(target);
            if(targetPiece==nullptr){
                moves.push_back(Move{from,target});
                step++;
            }else{
                if(targetPiece->getColor()!=this->getColor()){
                    moves.push_back(Move{from,target});
                }
                break;
            }
        }
    }
    return moves;
}
std::string Queen::getSymbol() const {
    return (m_color == Color::White) ? "Q" : "q";
}

std::vector<Move> Queen::getValidMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    static const std::vector<std::pair<int, int>> directions = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1},     
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}   
    };
    for(const auto& dir:directions){
        int step=1;
        while(true){
            Position target;
            target.row = from.row + (dir.first * step);
            target.col = from.col + (dir.second * step);
            if(!target.isValid()){
                break;
            }
            const Piece* targetPiece=board.getPieceAt(target);
            if(targetPiece==nullptr){
                moves.push_back(Move{from,target});
                step++;
            }else{
                if(targetPiece->getColor()!=this->getColor()){
                    moves.push_back(Move{from,target});
                }
                break;
            }
        }
    }
    return moves;
}

std::string King::getSymbol() const {
    return (m_color == Color::White) ? "K" : "k";
}

std::vector<Move> King::getValidMoves(const Board& board, const Position& from) const {
    std::vector<Move> moves;
    static const std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} 
    };

    for (const auto& dir : directions) {

        Position target;
        target.row = from.row + dir.first;
        target.col = from.col + dir.second;

        if (!target.isValid()) {
            continue; 
        }

        const Piece* targetPiece = board.getPieceAt(target);

        if (targetPiece == nullptr) {
            moves.push_back(Move{from, target});
        } else {
            if (targetPiece->getColor() != this->getColor()) {
                moves.push_back(Move{from, target});
            }
            
        }
    }


    return moves;
  }
}