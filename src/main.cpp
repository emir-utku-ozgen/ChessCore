#include <iostream>
#include "Game.hpp"
#include "Move.hpp"
#include "NotationParser.hpp"
#include "ChessException.hpp"

std::string colorToString(chess::Color color) {
    return (color == chess::Color::White) ? "WHITE" : "BLACK";
}

int main() {
    std::cout << "=========================================\n";
    std::cout << "   ChessCore - Edge Case Testing Suite   \n";
    std::cout << "=========================================\n\n";

    chess::Game game;

    // SENARYO 1: Sırası Olmayan Rengi Oynatmaya Çalışmak
    std::cout << "[SENARYO 1] Siyah Piyon a7 -> a6 (Sira Beyazda)\n";
    try {
        game.makeMove(chess::Move({6, 0}, {5, 0}));
        std::cout << "Hamle Sonucu: BASARILI (HATA! - exception firlamaliydi)\n";
    } catch (const chess::ChessException& e) {
        std::cout << "Hamle Sonucu: REDDEDILDI (DOGRU) - " << e.what() << "\n";
    }
    std::cout << "Aktif Sira: " << colorToString(game.getActiveColor()) << "\n";
    std::cout << "---------------------------------------------------------\n\n";

    // SENARYO 2: Boş Bir Kareden Hamle Denemek
    std::cout << "[SENARYO 2] Bos Kare {4,4} -> {5,4}\n";
    try {
        game.makeMove(chess::Move({4, 4}, {5, 4}));
        std::cout << "Hamle Sonucu: BASARILI (HATA! - exception firlamaliydi)\n";
    } catch (const chess::ChessException& e) {
        std::cout << "Hamle Sonucu: REDDEDILDI (DOGRU) - " << e.what() << "\n";
    }
    std::cout << "Aktif Sira: " << colorToString(game.getActiveColor()) << "\n";
    std::cout << "---------------------------------------------------------\n\n";

    // SENARYO 3: Kuralsız Hamle Denemek (Rook capraz)
    std::cout << "[SENARYO 3] Beyaz Kale a1 -> b2 (capraz, gecersiz)\n";
    try {
        game.makeMove(chess::Move({0, 0}, {1, 1}));
        std::cout << "Hamle Sonucu: BASARILI (HATA! - exception firlamaliydi)\n";
    } catch (const chess::ChessException& e) {
        std::cout << "Hamle Sonucu: REDDEDILDI (DOGRU) - " << e.what() << "\n";
    }
    std::cout << "Aktif Sira: " << colorToString(game.getActiveColor()) << "\n";
    std::cout << "=========================================\n\n";

    // ---------------------------------------------------------
    // SENARYO 4: Kendi Kralini Saha Atma (Self-Check) Testi
    // ---------------------------------------------------------
    std::cout << "=========================================\n";
    std::cout << "   Self-Check (Pinned Piece) Testing      \n";
    std::cout << "=========================================\n\n";

    chess::Game game2;
    game2.getBoard().clear();

    game2.getBoard().setPieceAt({0, 4}, std::make_unique<chess::King>(chess::Color::White));
    game2.getBoard().setPieceAt({1, 4}, std::make_unique<chess::Pawn>(chess::Color::White));
    game2.getBoard().setPieceAt({7, 4}, std::make_unique<chess::Rook>(chess::Color::Black));
    game2.getBoard().setPieceAt({2, 3}, std::make_unique<chess::Pawn>(chess::Color::Black));

    std::cout << "--- Kurulan Tahta ---\n";
    game2.getBoard().print();

    std::cout << "\nBeyaz Kral su an sahta mi? " << (game2.isInCheck(chess::Color::White) ? "EVET" : "HAYIR") << "\n";

    std::cout << "\n[TEST] Beyaz Piyon e2 x d3 (kralini acikta birakan hamle)\n";
    try {
        game2.makeMove(chess::Move({1, 4}, {2, 3}));
        std::cout << "Hamle Sonucu: BASARILI (HATA! - Kral tehlikede kaldi)\n";
    } catch (const chess::ChessException& e) {
        std::cout << "Hamle Sonucu: REDDEDILDI (DOGRU) - " << e.what() << "\n";
    }

    std::cout << "\n--- Tahta (Hamle Sonrasi, degismemis olmali) ---\n";
    game2.getBoard().print();
    std::cout << "Aktif Sira (degismemis olmali, hala WHITE): " << colorToString(game2.getActiveColor()) << "\n";
    std::cout << "=========================================\n\n";

    // ---------------------------------------------------------
    // SENARYO 5: NotationParser Save/Load Testi
    // ---------------------------------------------------------
    std::cout << "=========================================\n";
    std::cout << "   NotationParser Save/Load Testing       \n";
    std::cout << "=========================================\n\n";

    chess::Game game3;
    try {
        game3.makeMove(chess::Move({1, 4}, {3, 4})); // e2-e4
        game3.makeMove(chess::Move({6, 4}, {4, 4})); // e7-e5
        game3.makeMove(chess::Move({0, 6}, {2, 5})); // Ng1-f3
    } catch (const chess::ChessException& e) {
        std::cout << "Beklenmeyen hata (setup hamleleri gecerli olmali): " << e.what() << "\n";
    }

    std::cout << "--- Kaydedilecek Oyun (3 hamle sonrasi) ---\n";
    game3.getBoard().print();
    std::cout << "Hamle sayisi: " << game3.getMoveHistory().size() << "\n\n";

    try {
        chess::NotationParser::saveGame(game3, "test_game.txt");

        chess::Game loadedGame;
        chess::NotationParser::loadGame(loadedGame, "test_game.txt");

        std::cout << "\n--- Yuklenen Oyun ---\n";
        loadedGame.getBoard().print();
        std::cout << "Hamle sayisi: " << loadedGame.getMoveHistory().size() << "\n";

        bool sameMoveCount = (game3.getMoveHistory().size() == loadedGame.getMoveHistory().size());
        bool sameActiveColor = (game3.getActiveColor() == loadedGame.getActiveColor());
        std::cout << "\nHamle sayisi eslesiyor mu? " << (sameMoveCount ? "EVET" : "HAYIR") << "\n";
        std::cout << "Aktif renk eslesiyor mu? " << (sameActiveColor ? "EVET" : "HAYIR") << "\n";

    } catch (const std::exception& e) {
        std::cout << "HATA: " << e.what() << "\n";
    }

    std::cout << "=========================================\n";

    return 0;
}