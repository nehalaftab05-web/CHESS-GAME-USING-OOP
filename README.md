# CHESS-GAME-USING-OOP


A fully playable, two-player console-based Chess game built in **C++**. Both players take turns entering moves via keyboard on the same machine. All six piece types are implemented with their correct movement rules, path-blocking detection, and capture logic.

---

## 📋 Table of Contents

- [Gameplay](#gameplay)
- [Board Layout](#board-layout)
- [Controls](#controls)
- [Piece Representations](#piece-representations)
- [Code Structure](#code-structure)
- [Movement Rules Implemented](#movement-rules-implemented)
- [How to Build & Run](#how-to-build--run)
- [Known Limitations](#known-limitations)
- [Author](#author)

---

## Gameplay

Two players alternate turns on the same machine. White always goes first. On each turn, the active player enters a four-character move string representing the source and destination coordinates. The game validates the move against the piece's legal movement rules and either applies it or prompts the player to try again.

The game ends when a King is captured — no check or checkmate detection is implemented (see [Known Limitations](#known-limitations)).

---

## Board Layout

The board is an 8×8 grid addressed by `(x, y)` coordinates:

```
   y: 0  1  2  3  4  5  6  7
x:
 0    R  H  B  Q  K  B  H  R    ← White back rank
 1    P  P  P  P  P  P  P  P    ← White pawns
 2    ·  ·  ·  ·  ·  ·  ·  ·
 3    ·  ·  ·  ·  ·  ·  ·  ·
 4    ·  ·  ·  ·  ·  ·  ·  ·
 5    ·  ·  ·  ·  ·  ·  ·  ·
 6    p  p  p  p  p  p  p  p    ← Black pawns
 7    r  h  b  q  k  b  h  r    ← Black back rank
```

**Uppercase** = White pieces, **lowercase** = Black pieces.

---

## Controls

Moves are entered as a **4-digit string** — no spaces, no separators:

```
x1y1x2y2
```

| Part | Meaning |
|---|---|
| `x1y1` | Source square (row, column) |
| `x2y2` | Destination square (row, column) |

### Examples

| Input | Meaning |
|---|---|
| `1020` | Move piece at (1,0) to (2,0) |
| `0412` | Move piece at (0,4) to (1,2) |

---

## Piece Representations

| Symbol | Piece | Color |
|---|---|---|
| `K` | King | White |
| `k` | King | Black |
| `Q` | Queen | White |
| `q` | Queen | Black |
| `B` | Bishop | White |
| `b` | Bishop | Black |
| `H` | Knight | White |
| `h` | Knight | Black |
| `R` | Rook | White |
| `r` | Rook | Black |
| `P` | Pawn | White |
| `p` | Pawn | Black |

> Knight is represented as `H`/`h` to avoid confusion with King (`K`/`k`).

---

## Code Structure

```
chess-game/
│
├── chess.h       # Enums, class declarations (Square, Board)
└── chess.cpp     # Full implementation of all classes and methods
```

### Classes

**`Square`**
Represents a single cell on the board. Holds a `Piece` enum and a `Color` enum.

| Method | Role |
|---|---|
| `setPieceAndColor(p, c)` | Sets the piece and color of this square |
| `setSpace(Square*)` | Copies piece and color from another square (used for moving) |
| `setEmpty()` | Clears the square to `EMPTY` / `NONE` |
| `getPiece()` / `getColor()` | Accessors |
| `getX()` / `getY()` / `setX()` / `setY()` | Coordinate accessors |

**`Board`**
Holds the 8×8 `Square` grid and all game logic.

| Method | Role |
|---|---|
| `setBoard()` | Places all pieces in their starting positions |
| `printBoard()` | Renders the board to the console |
| `doMove()` | Reads player input, validates ownership, calls `makeMove()` |
| `makeMove(x1,y1,x2,y2)` | Bounds checks, friendly-fire check, dispatches to piece mover |
| `moveKing()` | One step in any direction |
| `moveQueen()` | Straight or diagonal, path-clear check |
| `moveBishop()` | Diagonal only, path-clear check |
| `moveKnight()` | L-shape (2+1), no path blocking |
| `moveRook()` | Straight lines only, path-clear check |
| `movePawn()` | Forward one step; diagonal capture only |
| `playGame()` | Clears screen, prints board, calls `doMove()` |

---

## Movement Rules Implemented

### King
Moves exactly one square in any direction (horizontal, vertical, or diagonal).

### Queen
Moves any number of squares in a straight line or diagonally. Blocked by any piece in the path.

### Bishop
Moves diagonally only. Verified by `abs(Δx) == abs(Δy)`. Blocked by any piece in the path.

### Knight
Moves in an L-shape: 2 squares in one axis and 1 in the other. Cannot be blocked by intermediate pieces.

### Rook
Moves horizontally or vertically any number of squares. Blocked by any piece in the path.

### Pawn
- Moves **forward one square** if the destination is empty
- Captures **diagonally forward** only if an enemy piece is present
- White pawns move in the `+y` direction; Black pawns move in the `-y` direction
- No double-step from starting position implemented

### Path Blocking (Queen, Bishop, Rook)
All sliding pieces check every intermediate square between source and destination. If any square has a non-`NONE` color, the move is rejected as blocked.

---

## How to Build & Run

### Requirements

- C++11 or later
- g++ or MSVC

### g++ / MinGW

```bash
g++ -o chess chess.cpp
./chess
```

### Visual Studio

```
1. Create a new Empty C++ Project
2. Add chess.h and chess.cpp to the project
3. Build → Run (Ctrl+F5)
```

### Playing

```
White's turn
Type in your move as a single four character string. Use x-coordinates first in each pair.
> 1020
```

The board reprints after every valid move. Invalid moves prompt the player to try again without losing their turn.

---

## Known Limitations

| Feature | Status |
|---|---|
| Check detection | ❌ Not implemented |
| Checkmate / Stalemate | ❌ Not implemented — game ends on King capture |
| Castling | ❌ Not implemented |
| En passant | ❌ Not implemented |
| Pawn promotion | ❌ Not implemented |
| Pawn double-step from start | ❌ Not implemented |
| Undo move | ❌ Not implemented |
| `std::cout` debug strings in Queen/Bishop | ⚠️ Left in (`"this"`, `"It got here somehow"`) |

These are known gaps from the initial implementation scope and are candidates for future improvement.

---

## Author

**Nehal Aftab**
Roll No: 24F-0518 · BCS-2E
FAST-NUCES CFD Campus, Faisalabad
