#include "NotationParser.hpp"
#include "ChessException.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
namespace chess{
std::string NotationParser::moveToString(const Move& move) {
    std::string result = "";
    
    char fromCol = 'a' + move.from.col;
    char toCol = 'a' + move.to.col;

    char fromRow = '1' + move.from.row;
    char toRow = '1' + move.to.row;

    result += fromCol;
    result += fromRow;
    result += "-";
    result += toCol;
    result += toRow;

    return result;
}

Move NotationParser::stringToMove(const std::string& str) {

    if (str.length() != 5 || str[2] != '-') {
        throw ChessException("Gecersiz hamle formati! Ornek format: e2-e4");
    }

    int fromCol = str[0] - 'a';
    int fromRow = str[1] - '1';
    int toCol = str[3] - 'a';
    int toRow = str[4] - '1';

    Position from{fromRow, fromCol};
    Position to{toRow, toCol};


    if (!from.isValid() || !to.isValid()) {
        throw InvalidPositionException("Girilen koordinatlar satranç tahtası sınırları dısında!");
    }

    return Move(from, to);
}

void NotationParser::saveGame(const Game& game, const std::string& filepath) {

    std::ofstream outFile(filepath);
    
    if (!outFile.is_open()) {
        throw ChessException("Dosya kaydedilemedi: " + filepath);
    }

    for (const auto& move : game.getMoveHistory()) {
        outFile << moveToString(move) << "\n";
    }

    outFile.close();
    std::cout << "[Sistem] Oyun basariyla kaydedildi: " << filepath << std::endl;
}

void NotationParser::loadGame(Game& game, const std::string& filepath) {

    std::ifstream inFile(filepath);

    if (!inFile.is_open()) {
        throw ChessException("Dosya yuklenemedi: " + filepath);
    }

    game = Game();

    std::string line;

    while (std::getline(inFile, line)) {

        if (line.empty()) continue;

        try {
            Move move = stringToMove(line);
            game.makeMove(move); 
        } catch (const std::exception& e) {
            inFile.close();
            throw ChessException("Dosya okunurken hata olustu: " + std::string(e.what()));
        }
    }

    inFile.close();
    std::cout << "[Sistem] Oyun basariyla yuklendi! Toplam hamle: " << game.getMoveHistory().size() << std::endl;
}
}