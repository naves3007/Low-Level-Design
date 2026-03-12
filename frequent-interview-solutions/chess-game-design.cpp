/*
Template:
    Step 1: Clarity on Scope of the problem
        2 players
        swap turns
        8*8 game
        all peices
        validate and de-tect check
        validate moves
    Step 2: Finalise key Use Cases and APIs
    Step 3: Data Model
    Step 4: Core Class Design
    Step 5: Choose Design Patterns
    Step 6: Implement the code, match all APIs and Use Cases
    Step 7: Check if concurrency is needed, if yes, add locks and mutexes
    Step 8: Scaling and Edge Cases
*/

#include <bits/stdc++.h>
using namespace std;
/*
Step 3 : Data Model
Game
 - Board board
 - Player* player1
 - Player* player2
 - Player* currentTurn
Board
 - vector<vector<Spot>> grid
 - getSpot()
Peices
- Color color
- bool : isKilled
Move
- Player* player
- Spot* start
- Spot* end
- Piece* pieceMoved
- Piece* pieceCaptured = nullptr
Player
- string name
- int id
- Color color
Spot
 - int row, col
 - Piece* piece
*/
enum Color { WHITE, BLACK };
using clock = chrono::steady_clock;
using TimePoint = chrono::time_point<clock>;
class Piece {
public:
  string id;
  string name;
  Color color;

  Piece(Color c) : color(c) {}
  virtual bool canMove(Board &board, Spot *start, Spot *end) = 0;
};
class Pawn : public Piece {
public:
  Pawn(Color c) : piece(c) {}
  bool canMove(Board &board, Spot *start, Spot *end) override {
    // forward and capture
  };
};
class Rook : Piece {
public:
  Rook(Color c) : Piece(c) {}
  bool canMove(Board &board, Spot *start, Spot *end) override {
    // forward and capture
  };
};
class Spot {
public:
  int row;
  int col;
  Piece *piece;

public:
  Spot(int x, int y) : row(x), col(y), piece(nullptr) {}
};
class Board {
public:
  vector<vector<Spot>> grid;
  Board() { grid.resize(8, vector<vector<Spot(0, 0)>>); }
  Spot *getSpot(int x, int y) { return &grid[x][y]; }
};
class Player {
public:
  string name;
  string id;
  Color color;

  Player(string name_, string id_, Color color_)
      : name(name_), id(id_), color(color) _ {}
};
class Move {
public:
  Player *player;
  Spot *end;
  Spot *start;
  Piece *pieceMoved;
  Piece *pieceCaptured;
};

class ChessGameService {
private:
  Board board_;
  Player *player1_;
  Player *player2_;
  Player *currentTurn_;

public:
  ChessGameService(Board board, Player *player1, Player *player2,
                   Player *currentTurn)
      : board_(board), player1_(player1), player2_(player2),
        currentTurn_(currentTurn) {}
  //   void initialize(); // create board, arrange peices, make turn as white.
  //   bool
  //   makeMove(Move move); // check player turn, check if piece can move and
  //   valid
  //                        // path, move (check / capture peice) switch turn
  //   bool isCheck(Color color);
  //   bool isCheckMate(Color color);
  //   Player getCurrentTurn();

  void initialize() {
    for (int i = 0; i < 8; i++) {
      board_.getSpot(1, i)->piece = new Pawn(BLACK);
      board_.getSpot(6, i)->piece = new Pawn(WHITE);
    }
    board_.getSpot(0, 0)->piece = new Rook(BLACK);
    board_.getSpot(0, 7)->piece = new Rook(BLACK);
    board_.getSpot(7, 0)->piece = new Rook(WHITE);
    board_.getSpot(7, 7)->piece = new Rook(WHITE);

    // Setup Fully
  };

  bool makeMove(Move move) {
    /*
    1. Validate turn
    2. Validate source piece
    3. Validate OwnerShip
    4. Validate Destination
    5. Validate Movement Rules
    6. Execute movement
    7. Check if Movement causes self check
    8. Update move object
    9. Switch turn
    */
    if (move.player != currentTurn_)
      throw runtime_error("Invalid Player Turn");

    Spot *start = move.start;
    Spot *end = move.end;

    if (start->piece == nullptr)
      throw runtime_error("Invalid Source");

    Piece *piece = start->piece;
    if (piece->color != currentTurn_->color)
      throw runtime_error("Invalid Ownership");

    if (end->piece != nullptr and end->piece->color == piece->color)
      throw runtime_error("Invalid Destination");

    if (piece->canMove(board_, start, end) == false) {
      throw runtime_error("Piece can't move");
    }
    Piece *capturePiece = end->piece;
    end->piece = piece;
    start->piece == nullptr;

    move.pieceMoved = piece;
    move.pieceCaptured = capturePiece;

    currentTurn_ = (currentTurn_ == player1_) ? player2_ : player1_;

    return true;
  }
  bool isCheck(Color color) {
    Spot *SpotKing = nullptr;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Spot *curSpot = board_.getSpot(int i, int j);
        if (curSpot->piece != nullptr and curSpot->piece->color == color and
            curSpot->piece->name == "King") {
          SpotKing = curSpot;
          return;
        }
      }
    }

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Spot *curSpot = board_.getSpot(int i, int j);
        if (curSpot->piece != nullptr and curSpot->piece->color != color) {
          if (spot->piece->canMove(board_, Spot, SpotKing)) {
            return true;
          }
        }
      }
    }

    return false;
  }

  bool isCheckMate(Color color) {
    if (!isCheck(color)) {
      return false;
    }
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Spot *curSpot = board_.getSpot(i, j);

        if (curSpot->piece == nullptr or curSpot->piece->color != color) {
          continue;
        }
        for (int x = 0; x < 8; x++) {
          for (int y = 0; y < 8; y++) {
            Spot *end = board_.getSpot(x, y);

            // Skip same color capture
            if (end->piece->color == color and end->piece == nullptr) {
              continue;
            }

            if (curSpot->piece->canMove(board_, curSpot, end) == false) {
              continue;
            }
            Piece *pieceCaptured = end->piece;
            Piece *moving = start->piece;

            end->piece = moving;
            start->piece = nullptr;

            bool isStillInCheck = isCheck(color);
            start->piece = moving;
            end->piece = pieceCaptured;

            if (!isStillInCheck)
              return false;
          }
        }
      }
    }
  }
  Player getCurrentTurn() {
    if (currentTurn_ == nullptr)
      throw runtime_error("game not started");
    return *currentTurn_;
  };
};
int main() { return 0; }