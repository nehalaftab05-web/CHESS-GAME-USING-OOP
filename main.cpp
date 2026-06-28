// =====================================================
//  COMPLETE OOP CHESS GAME - NUCES PROJECT
//  Demonstrates: Inheritance, Polymorphism, Composition, Encapsulation
//  Compiles with: g++ -std=c++17 ChessGame.cpp -o chess
// =====================================================

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Forward declaration
class Board;

// =====================================================
// Enums
// =====================================================
enum Color { WHITE, BLACK, NONE };
enum PieceType { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

// =====================================================
// Base Class: Piece (Demonstrates Inheritance & Polymorphism)
// =====================================================
// base class is abstract class here
class Piece {
protected:
    Color color;        // Encapsulation: protected data members
    int x, y;
    bool hasMoved;      // Track if piece has moved (for castling, pawn double move)

public:
    // Constructor
    Piece(Color c, int px, int py) : color(c), x(px), y(py), hasMoved(false) {}

    // Virtual destructor for polymorphism
    virtual ~Piece() = default;

    // Accessor methods (Encapsulation)
    Color getColor() const { return color; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool getHasMoved() const { return hasMoved; }

    void setPosition(int nx, int ny) {
        x = nx;
        y = ny;
        hasMoved = true;
    }

    // Pure virtual functions (Polymorphism)
    //these functions make it abstract class
    virtual bool isValidMove(int toX, int toY, const Board* board) const = 0;
    virtual char getSymbol() const = 0;
    virtual PieceType getType() const = 0;
    virtual string getName() const = 0;
};

// =====================================================
// Derived Piece Classes (Inheritance)
// =====================================================

class King : public Piece {
public:
    King(Color c, int x, int y) : Piece(c, x, y) {}

    char getSymbol() const override {
        return color == WHITE ? 'K' : 'k';
    }

    PieceType getType() const override {
        return KING;
    }

    string getName() const override {
        return "King";
    }

    bool isValidMove(int toX, int toY, const Board* board) const override {
        // King moves one square in any direction
        int dx = abs(toX - x);
        int dy = abs(toY - y);
        return (dx <= 1 && dy <= 1 && (dx != 0 || dy != 0));
    }
};

class Queen : public Piece {
public:
    Queen(Color c, int x, int y) : Piece(c, x, y) {}

    char getSymbol() const override {
        return color == WHITE ? 'Q' : 'q';
    }

    PieceType getType() const override {
        return QUEEN;
    }

    string getName() const override {
        return "Queen";
    }

    bool isValidMove(int toX, int toY, const Board* board) const override;
};

class Rook : public Piece {
public:
    Rook(Color c, int x, int y) : Piece(c, x, y) {}

    char getSymbol() const override {
        return color == WHITE ? 'R' : 'r';
    }

    PieceType getType() const override {
        return ROOK;
    }

    string getName() const override {
        return "Rook";
    }

    bool isValidMove(int toX, int toY, const Board* board) const override;
};

class Bishop : public Piece {
public:
    Bishop(Color c, int x, int y) : Piece(c, x, y) {}

    char getSymbol() const override {
        return color == WHITE ? 'B' : 'b';
    }

    PieceType getType() const override {
        return BISHOP;
    }

    string getName() const override {
        return "Bishop";
    }

    bool isValidMove(int toX, int toY, const Board* board) const override;
};

class Knight : public Piece {
public:
    Knight(Color c, int x, int y) : Piece(c, x, y) {}

    char getSymbol() const override {
        return color == WHITE ? 'N' : 'n';
    }

    PieceType getType() const override {
        return KNIGHT;
    }

    string getName() const override {
        return "Knight";
    }

    bool isValidMove(int toX, int toY, const Board* board) const override {
        // Knight moves in L-shape: 2 squares in one direction, 1 in perpendicular
        int dx = abs(toX - x);
        int dy = abs(toY - y);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
};

class Pawn : public Piece {
public:
    Pawn(Color c, int x, int y) : Piece(c, x, y) {}

    char getSymbol() const override {
        return color == WHITE ? 'P' : 'p';
    }

    PieceType getType() const override {
        return PAWN;
    }

    string getName() const override {
        return "Pawn";
    }

    bool isValidMove(int toX, int toY, const Board* board) const override;
};

// =====================================================
// Square Class (Demonstrates Composition)
// =====================================================
class Square {
private:
    Piece* piece;  // Encapsulation: private data member

public:
    Square() : piece(nullptr) {}

    ~Square() {
        // Clean up dynamically allocated piece
        if (piece != nullptr) {
            delete piece;
        }
    }

    void place(Piece* p) {
        piece = p;
    }

    void remove() {
        piece = nullptr;
    }

    Piece* getPiece() const {
        return piece;
    }

    bool isEmpty() const {
        return piece == nullptr;
    }

    char display() const {
        return piece ? piece->getSymbol() : '.';
    }
};

// =====================================================
// Board Class (Demonstrates Composition & Encapsulation)
// =====================================================
class Board {
private:
    Square squares[8][8];  // Composition: Board contains Square objects
    Color currentTurn;
    bool gameOver;
    Color winner;

public:
    Board() : currentTurn(WHITE), gameOver(false), winner(NONE) {
        setupBoard();
    }

    ~Board() {
        // Cleanup is handled by Square destructors
    }

    // Public methods
    void display() const;
    void setupBoard();
    bool makeMove(int x1, int y1, int x2, int y2);
    bool isPathClear(int x1, int y1, int x2, int y2) const;
    bool isInCheck(Color color) const;
    bool isCheckmate(Color color);
    bool isStalemate(Color color);
    bool hasValidMoves(Color color);

    Piece* getPieceAt(int x, int y) const {
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
            return squares[x][y].getPiece();
        return nullptr;
    }

    Color getCurrentTurn() const { return currentTurn; }
    bool isGameOver() const { return gameOver; }
    Color getWinner() const { return winner; }

private:
    void switchTurn() {
        currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
    }

    bool wouldBeInCheck(int x1, int y1, int x2, int y2, Color color);
};

// =====================================================
// Board Helper Functions
// =====================================================

void Board::setupBoard() {
    // Clear the board first
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            squares[x][y].remove();
        }
    }

    // Setup White pieces (bottom - rows 0 and 1)
    squares[0][0].place(new Rook(WHITE, 0, 0));
    squares[1][0].place(new Knight(WHITE, 1, 0));
    squares[2][0].place(new Bishop(WHITE, 2, 0));
    squares[3][0].place(new Queen(WHITE, 3, 0));
    squares[4][0].place(new King(WHITE, 4, 0));
    squares[5][0].place(new Bishop(WHITE, 5, 0));
    squares[6][0].place(new Knight(WHITE, 6, 0));
    squares[7][0].place(new Rook(WHITE, 7, 0));

    for (int x = 0; x < 8; ++x) {
        squares[x][1].place(new Pawn(WHITE, x, 1));
    }

    // Setup Black pieces (top - rows 6 and 7)
    squares[0][7].place(new Rook(BLACK, 0, 7));
    squares[1][7].place(new Knight(BLACK, 1, 7));
    squares[2][7].place(new Bishop(BLACK, 2, 7));
    squares[3][7].place(new Queen(BLACK, 3, 7));
    squares[4][7].place(new King(BLACK, 4, 7));
    squares[5][7].place(new Bishop(BLACK, 5, 7));
    squares[6][7].place(new Knight(BLACK, 6, 7));
    squares[7][7].place(new Rook(BLACK, 7, 7));

    for (int x = 0; x < 8; ++x) {
        squares[x][6].place(new Pawn(BLACK, x, 6));
    }
}

void Board::display() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "\n========================================\n";
    cout << "     CHESS GAME - OOP PROJECT (NUCES)\n";
    cout << "========================================\n\n";
    cout << "  Current Turn: " << (currentTurn == WHITE ? "WHITE" : "BLACK") << "\n\n";

    cout << "     0   1   2   3   4   5   6   7  (X)\n";
    cout << "   +---+---+---+---+---+---+---+---+\n";

    for (int y = 7; y >= 0; --y) {  // Display from top to bottom (7 to 0)
        cout << " " << y << " |";
        for (int x = 0; x < 8; ++x) {
            cout << " " << squares[x][y].display() << " |";
        }
        cout << " " << y << " (Y)\n";
        cout << "   +---+---+---+---+---+---+---+---+\n";
    }

    cout << "     0   1   2   3   4   5   6   7  (X)\n\n";
    cout << "White pieces: K Q R B N P\n";
    cout << "Black pieces: k q r b n p\n\n";
}

bool Board::isPathClear(int x1, int y1, int x2, int y2) const {
    // Check if path is clear between two squares (for sliding pieces)
    int dx = (x2 > x1) ? 1 : (x2 < x1) ? -1 : 0;
    int dy = (y2 > y1) ? 1 : (y2 < y1) ? -1 : 0;

    int x = x1 + dx;
    int y = y1 + dy;

    while (x != x2 || y != y2) {
        if (!squares[x][y].isEmpty()) {
            return false;
        }
        x += dx;
        y += dy;
    }

    return true;
}

bool Board::isInCheck(Color color) const {
    // Find the King's position
    int kingX = -1, kingY = -1;

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* piece = squares[x][y].getPiece();
            if (piece && piece->getType() == KING && piece->getColor() == color) {
                kingX = x;
                kingY = y;
                break;
            }
        }
        if (kingX != -1) break;
    }

    if (kingX == -1) return false;  // King not found (shouldn't happen)

    // Check if any opponent piece can attack the King
    Color opponentColor = (color == WHITE) ? BLACK : WHITE;

    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Piece* piece = squares[x][y].getPiece();
            if (piece && piece->getColor() == opponentColor) {
                if (piece->isValidMove(kingX, kingY, this)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::wouldBeInCheck(int x1, int y1, int x2, int y2, Color color) {
    // Simulate the move and check if it results in check
    Piece* movingPiece = squares[x1][y1].getPiece();
    Piece* capturedPiece = squares[x2][y2].getPiece();

    int oldX = movingPiece->getX();
    int oldY = movingPiece->getY();

    // Make the move temporarily
    squares[x2][y2].place(movingPiece);
    squares[x1][y1].remove();
    movingPiece->setPosition(x2, y2);

    bool inCheck = isInCheck(color);

    // Undo the move
    squares[x1][y1].place(movingPiece);
    squares[x2][y2].place(capturedPiece);
    movingPiece->setPosition(oldX, oldY);

    return inCheck;
}

bool Board::hasValidMoves(Color color) {
    // Check if the player has any valid moves
    for (int x1 = 0; x1 < 8; ++x1) {
        for (int y1 = 0; y1 < 8; ++y1) {
            Piece* piece = squares[x1][y1].getPiece();
            if (piece && piece->getColor() == color) {
                // Try all possible destination squares
                for (int x2 = 0; x2 < 8; ++x2) {
                    for (int y2 = 0; y2 < 8; ++y2) {
                        if (x1 == x2 && y1 == y2) continue;

                        // Check basic move validity
                        if (!piece->isValidMove(x2, y2, this)) continue;

                        Piece* target = squares[x2][y2].getPiece();
                        if (target && target->getColor() == color) continue;

                        // Check if move would leave king in check
                        if (!wouldBeInCheck(x1, y1, x2, y2, color)) {
                            return true;  // Found a valid move
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(Color color) {
    return isInCheck(color) && !hasValidMoves(color);
}

bool Board::isStalemate(Color color) {
    return !isInCheck(color) && !hasValidMoves(color);
}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
    // Validate coordinates
    if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 ||
        x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7) {
        cout << "Error: Coordinates out of bounds!\n";
        return false;
    }

    // Check if source square has a piece
    Piece* piece = squares[x1][y1].getPiece();
    if (!piece) {
        cout << "Error: No piece at source position!\n";
        return false;
    }

    // Check if it's the correct player's turn
    if (piece->getColor() != currentTurn) {
        cout << "Error: Not your turn! It's "
            << (currentTurn == WHITE ? "WHITE" : "BLACK") << "'s turn.\n";
        return false;
    }

    // Check if move is valid according to piece rules
    if (!piece->isValidMove(x2, y2, this)) {
        cout << "Error: Invalid move for " << piece->getName() << "!\n";
        return false;
    }

    // Check if trying to capture own piece
    Piece* target = squares[x2][y2].getPiece();
    if (target && target->getColor() == currentTurn) {
        cout << "Error: Cannot capture your own piece!\n";
        return false;
    }

    // Check if move would put own king in check
    if (wouldBeInCheck(x1, y1, x2, y2, currentTurn)) {
        cout << "Error: This move would put your King in check!\n";
        return false;
    }

    // Execute the move
    Piece* capturedPiece = squares[x2][y2].getPiece();
    squares[x2][y2].place(piece);
    squares[x1][y1].remove();
    piece->setPosition(x2, y2);

    // Display capture message
    if (capturedPiece) {
        cout << ">> " << (currentTurn == WHITE ? "White" : "Black")
            << " captured " << capturedPiece->getName() << "!\n";
        delete capturedPiece;
    }

    // Switch turns
    switchTurn();

    // Check for checkmate
    if (isCheckmate(currentTurn)) {
        gameOver = true;
        winner = (currentTurn == WHITE) ? BLACK : WHITE;
        cout << "\n+================================+\n";
        cout << "|          CHECKMATE!            |\n";
        cout << "|   " << (winner == WHITE ? "WHITE" : "BLACK") << " WINS THE GAME!        |\n";
        cout << "+================================+\n";
        return true;
    }

    // Check for stalemate
    if (isStalemate(currentTurn)) {
        gameOver = true;
        winner = NONE;
        cout << "\n+================================+\n";
        cout << "|          STALEMATE!            |\n";
        cout << "|      GAME IS A DRAW            |\n";
        cout << "+================================+\n";
        return true;
    }

    // Check for regular check
    if (isInCheck(currentTurn)) {
        cout << ">> CHECK! " << (currentTurn == WHITE ? "White" : "Black")
            << " King is under attack!\n";
    }

    return false;
}

// =====================================================
// Piece Move Implementations
// =====================================================

bool Queen::isValidMove(int toX, int toY, const Board* board) const {
    // Queen moves like rook OR bishop
    int dx = abs(toX - x);
    int dy = abs(toY - y);

    // Same row, same column, or diagonal
    if (!((dx == dy) || (x == toX) || (y == toY))) {
        return false;
    }

    // Check if path is clear
    return board->isPathClear(x, y, toX, toY);
}

bool Rook::isValidMove(int toX, int toY, const Board* board) const {
    // Rook moves horizontally or vertically
    if (x != toX && y != toY) {
        return false;
    }

    // Check if path is clear
    return board->isPathClear(x, y, toX, toY);
}

bool Bishop::isValidMove(int toX, int toY, const Board* board) const {
    // Bishop moves diagonally
    if (abs(toX - x) != abs(toY - y)) {
        return false;
    }

    // Check if path is clear
    return board->isPathClear(x, y, toX, toY);
}

bool Pawn::isValidMove(int toX, int toY, const Board* board) const {
    int direction = (color == WHITE) ? 1 : -1;  // White moves up, Black moves down
    int startRow = (color == WHITE) ? 1 : 6;

    // Moving forward
    if (toX == x) {
        // Single step forward
        if (toY == y + direction && board->getPieceAt(toX, toY) == nullptr) {
            return true;
        }

        // Double step from starting position
        if (y == startRow && toY == y + 2 * direction) {
            if (board->getPieceAt(x, y + direction) == nullptr &&
                board->getPieceAt(toX, toY) == nullptr) {
                return true;
            }
        }
    }
    // Diagonal capture
    else if (abs(toX - x) == 1 && toY == y + direction) {
        Piece* target = board->getPieceAt(toX, toY);
        if (target && target->getColor() != color) {
            return true;
        }
    }

    return false;
}

// =====================================================
// Main Function
// =====================================================

int main() {
    cout << "\n";
    cout << "================================================\n";
    cout << "                                                \n";
    cout << "           CHESS GAME IN C++                    \n";
    cout << "                                                \n";
    cout << "      Object-Oriented Programming Project       \n";
    cout << "      NUCES - Faisalabad-Chiniot Campus         \n";
    cout << "                                                \n";
    cout << "================================================\n\n";

    cout << "Demonstrating OOP Concepts:\n";
    cout << "  > Encapsulation (private data members)\n";
    cout << "  > Inheritance (Piece -> King, Queen, etc.)\n";
    cout << "  > Polymorphism (virtual functions)\n";
    cout << "  > Composition (Board contains Squares)\n\n";

    Board board;
    string input;
    int x1, y1, x2, y2;

    cout << "How to Play:\n";
    cout << "  * Enter moves as 4 digits: FromX FromY ToX ToY\n";
    cout << "  * Example: 0140 moves piece from (0,1) to (4,0)\n";
    cout << "  * White pieces: K Q R B N P (uppercase)\n";
    cout << "  * Black pieces: k q r b n p (lowercase)\n";
    cout << "  * Type 'quit' to exit\n\n";

    cout << "Press Enter to start the game...";
    cin.get();

    while (!board.isGameOver()) {
        board.display();

        cout << "Enter your move (or 'quit' to exit): ";
        cin >> input;

        if (input == "quit" || input == "exit") {
            cout << "\nThanks for playing!\n";
            break;
        }

        if (input.length() != 4) {
            cout << "Invalid input! Please enter exactly 4 digits.\n";
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        // Parse input
        x1 = input[0] - '0';
        y1 = input[1] - '0';
        x2 = input[2] - '0';
        y2 = input[3] - '0';

        // Attempt move
        bool gameEnded = board.makeMove(x1, y1, x2, y2);

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();

        if (gameEnded) {
            board.display();
            break;
        }
    }

    cout << "\n================================================\n";
    cout << "            GAME OVER - THANK YOU!              \n";
    cout << "================================================\n\n";

    return 0;
}