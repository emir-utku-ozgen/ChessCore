# ChessCore

A modular, object-oriented **Chess Rule Engine** written in Modern C++ (C++20).

ChessCore is not a full chess *game* — there's no AI opponent and no GUI. It's a focused **rules engine**: a clean domain model that knows how pieces move, whether a king is in check, and how to advance game state one legal move at a time. The goal of this project was to practice designing a multi-file C++ architecture around RAII, ownership semantics, polymorphism, and exception handling, rather than to ship a playable app.

## Features

- **Full board representation** — an 8x8 grid of uniquely-owned pieces (`std::unique_ptr<Piece>`), with standard algebraic-style ASCII rendering
- **Complete movement rules for all six piece types**, including:
  - Sliding movement for Rook, Bishop, and Queen (ray-casting in a direction until blocked)
  - Fixed-offset movement for Knight and King
  - Full Pawn logic: single/double advance from the starting rank, diagonal captures, and directionality based on color
- **Turn-based game state** — `Game` tracks the active color, validates that a move belongs to the current player, and maintains a move history
- **Check detection** — locates the king via `dynamic_cast` and determines whether any enemy piece's legal moves include the king's square
- **Self-check prevention** — `makeMove()` provisionally applies a move, re-checks king safety, and reverts the move (including restoring any captured piece) if it would leave the mover's own king in check. Verified against a pinned-piece scenario (king behind a pawn behind an enemy rook on the same file).
- **Exception-driven error handling** — `makeMove()` throws a typed `IllegalMoveException` (with a specific message) for every rejection case: no piece at the source square, wrong player's turn, a move outside the piece's legal move set, or a move that would leave the mover's own king in check. Callers use `try`/`catch` rather than checking a boolean return value.
- **Save/load, fully verified** — `NotationParser` converts moves to/from a simple `e2-e4`-style string format and reads/writes full games to disk. A save → load round trip has been tested end-to-end: the reloaded game reproduces an identical board, move count, and active color.

## What's *not* implemented yet

Being upfront about scope is part of the point:

- Checkmate / stalemate detection (currently only single-position check detection exists — a king can be "in check" but there's no detection of *no legal moves remain*)
- Castling, en passant, and pawn promotion
- No automated test suite yet — correctness has been verified manually via `try`/`catch` scenarios and printed board states in `main.cpp`, not via a framework like Catch2 or GoogleTest

See [Roadmap](#roadmap) below for where this is headed.

## Architecture

```
ChessCore/
├── CMakeLists.txt
├── include/
│   ├── Position.hpp        # Board coordinate (row, col) + validity check
│   ├── Piece.hpp            # Abstract Piece base + 6 concrete piece classes
│   ├── Move.hpp              # from/to pair representing a single move
│   ├── Board.hpp              # Owns the 8x8 grid, exposes query/mutation API
│   ├── Game.hpp                # Turn management, move legality, check detection
│   ├── NotationParser.hpp       # Move <-> string conversion, save/load
│   └── ChessException.hpp        # ChessException base + IllegalMoveException / InvalidPositionException
├── src/
│   ├── Board.cpp
│   ├── Piece.cpp
│   ├── Game.cpp
│   ├── NotationParser.cpp
│   ├── Move.cpp              # intentionally minimal — Move is header-only
│   └── main.cpp               # manual verification / demo entry point
```

### Dependency chain

`Position` → `Piece` → `Board` → `Game` → `NotationParser`

Each layer only knows about the one below it. `Piece` forward-declares `Board` (rather than including it) to avoid a circular include, since `Board` owns `Piece` instances while `Piece::getValidMoves()` needs to query the `Board` it's placed on.

### Design decisions worth calling out

- **Ownership vs. observation.** The board owns its pieces via `std::unique_ptr<Piece>`. Query methods like `getPieceAt()` return a raw, non-owning `Piece*` — callers can look but not take ownership. Methods that transfer ownership (`removePieceAt()`) return a `std::unique_ptr<Piece>` explicitly, making the ownership transfer visible in the type signature.
- **Open/Closed movement rules.** Each piece implements its own `virtual getValidMoves()`. Adding a new or custom piece type requires zero changes to `Board` or `Game` — the polymorphic dispatch handles it.
- **Move safety via temporary application.** Rather than duplicating board state to test "would this move cause check," `Game::makeMove()` applies the move in place, checks the resulting state, and rolls it back if invalid — restoring any captured piece via RAII rather than manual cleanup.
- **Exceptions over silent failure.** `makeMove()` and `NotationParser`'s I/O methods return `void` and throw on failure, rather than returning a `bool`/error code. Every rejection reason gets its own descriptive message via a small exception hierarchy (`ChessException` → `IllegalMoveException` / `InvalidPositionException`), so callers can distinguish *why* a move failed instead of just knowing that it did.

## Getting Started

### Requirements
- CMake ≥ 3.15
- A C++20-capable compiler (Clang, GCC, or MSVC)

### Build
```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

### Run
```bash
./chess_core
```

`main.cpp` runs a manual verification suite covering five scenarios: rejected moves (wrong turn, empty square, illegal piece movement — each caught via `try`/`catch` and printing the specific exception message), a pinned-piece self-check scenario, and a full save/load round trip through `NotationParser`.

## Example

```cpp
chess::Game game;

try {
    game.makeMove(chess::Move{{1, 4}, {3, 4}}); // pawn e2-e4 equivalent
    game.getBoard().print();
} catch (const chess::ChessException& e) {
    std::cout << "Move rejected: " << e.what() << "\n";
}
```

## Roadmap

- [ ] Checkmate and stalemate detection
- [ ] Castling, en passant, pawn promotion
- [ ] Replace the manual `main.cpp` verification suite with an automated test framework (Catch2 or GoogleTest)

## License

MIT (or update to whatever license you prefer before publishing).