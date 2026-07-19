#pragma once
namespace chess{
    struct Position{
        int row;
        int col;
        Position(int r, int c) : row(r), col(c) {}
        Position() : row(0), col(0) {}
        bool operator==(const Position& other)const{
            return row==other.row && col==other.col;
        }
        bool isValid()const{
            return row>=0 && row<8 && col>=0 && col<8;
        }
    };
}