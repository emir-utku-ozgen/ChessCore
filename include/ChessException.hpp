#pragma once
#include <stdexcept>
#include <string>

namespace chess{
    class ChessException: public std::runtime_error{
        public:
        explicit ChessException (const std:: string& message):std::runtime_error(message){}
        };
    class IllegalMoveException : public ChessException {
        public:
        explicit IllegalMoveException(const std::string& message) 
        : ChessException("Gecersiz Hamle: " + message) {}
        };
    class InvalidPositionException : public ChessException {
        public :
        explicit InvalidPositionException(const std::string& message)
        :ChessException("Geçersiz Koordinat: "+message){}
    };
}