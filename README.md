# ChessCore

A modular, object-oriented **Chess Rule Engine** written in Modern C++ (C++20).

ChessCore is not a full chess *game* — there's no AI opponent and no GUI. It's a focused **rules engine**: a clean domain model that knows how pieces move, whether a king is in check, and how to advance game state one legal move at a time. The goal of this project was to practice designing a multi-file C++ architecture around RAII, ownership semantics, and polymorphism, rather than to ship a playable app.

## Features

- **Full board representation** — an 8x8 grid of uniquely-owned pieces (`std::unique_ptr<Piece>`), with standard algebraic-style ASCII rendering
- **Complete movement rules for all six piece types**, including:
  - Sliding movement for Rook, Bishop, and Queen (ray-casting in a direction until blocked)
  - Fixed-offset movement for Knight and King
  - Full Pawn logic: single/double advance from the starting rank, diagonal captures, and directionality based on color
- **Turn-based game state** — `Game` tracks the active color, validates that a move belongs to the current player, and maintains a move history
- **Check detection** — locates the king via `dynamic_cast` and determines whether any enemy piece's legal moves include the king's square
- **Self-check prevention** — `makeMove()` provisionally applies a move, re-checks king safety, and reverts the move (including restoring any captured piece) if it would leave the mover's own king in check
- **Save/load scaffolding** — a `NotationParser` for converting moves to/from a simple string format and reading/writing games to disk

## What's *not* implemented yet

This is a work in progress, and being upfront about scope is part of the point:

- Checkmate / stalemate detection (currently only single-position check detection exists)
- Castling, en passant, and pawn promotion
- `ChessException` is defined but not yet thrown anywhere — invalid moves in `makeMove()` currently fail silently (a `return`, not an error)
- No automated test suite yet — correctness has been verified manually via printed board states in `main.cpp`
- `NotationParser` is implemented but not yet exercised by any test

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
│   └── ChessException.hpp        # Custom exception type (not yet wired up)
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

The current `main.cpp` runs a manual verification sequence: it sets up the board, prints it, generates legal moves for a knight, and plays through a couple of `Game::makeMove()` calls to demonstrate turn switching and move rejection.

## Example

```cpp
chess::Game game;
game.makeMove(chess::Move{{1, 4}, {3, 4}}); // pawn e2-e4 equivalent
game.getBoard().print();
```

## Roadmap

- [ ] Throw `ChessException` on illegal moves instead of silently ignoring them
- [ ] Checkmate and stalemate detection
- [ ] Castling, en passant, pawn promotion
- [ ] Exercise and validate `NotationParser` save/load round-trips
- [ ] Add an automated test suite (currently verification is manual, via `main.cpp`)

## License

MIT (or update to whatever license you prefer before publishing).