
#pragma once
#include "Move.hpp"
#include "Game.hpp"
#include <string>
#include <vector>

namespace chess {

class NotationParser {
public:
    static std::string moveToString(const Move& move);
    static Move stringToMove(const std::string& str);
    static void saveGame(const Game& game, const std::string& filepath);
    static void loadGame(Game& game, const std::string& filepath);
    };
} 