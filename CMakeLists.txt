cmake_minimum_required(VERSION 3.15)
project(ChessCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(chess_core
    src/main.cpp
    src/Piece.cpp
    src/Board.cpp
    src/Move.cpp
    src/Game.cpp
)
