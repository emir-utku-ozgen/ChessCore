#pragma once
#include "Position.hpp"
namespace chess{
    struct Move{
        Position from;
        Position to;
        Move(Position f,Position t):from(f),to(t){}
        bool operator==(const Move& other)const{
            return from==other.from && to==other.to;
        }
    };
}