#include <bits/stdc++.h>
using namespace std;
/*
    Data Model:
*/
enum Color { BLACK, WHITE };
class Spot {
  int row;
  int col;
  Piece *piece;
};
class Board {
public:
  vector<vector<Spot *>> grid;
  Spot *getSpot(int x, int y) { return &grid(x, y); }
};
class Piece {
public:
  Color color;
  string name;
  virtual void canMove(Spot *start, Spot *end, Board &board){} = 0;
};
class Rook : public Piece {
public:
  void canMove(Spot *start, Spot *end, Board &board) override {
    // how a rook can move
  }
};
class Pawn : public Piece {
  Color color;

public:
  void canMove(Spot *start, Spot *end, Board &board) override {
    // how a Pawn can move
  }
  Pawn(Color color) : color(color) {}
};
class Queen : public Piece {
public:
  void canMove(Spot *start, Spot *end, Board &board) override {
    // how a Queen can move
  }
};
class Player {
public:
  string name;
  Color color;
};
class Move {
public:
  Spot *start;
  Spot *end;
  Piece *pieceCaptured;
  Piece *moved;
  Player *player;
};
class CheckGameService() {
private:
  Player *player1_;
  Player *player2_;
  Player *currentPlayer_;
  Board *board_;

public:
  CheckGameService(Player *player1, Player *player2, Player *currentPlayer,
                   Board *board) {
    player1_(player1), player2_(player2_), currentPlayer_(currentPlayer),
        board_(board) {}
  }
  void initialize() {
    for (int i = 0; i < 8; i++) {
      board_.getSpot(1, i)->piece = new Pawn(BLACK);
      board_.getSpot(7, i)->piece = new Pawn(WHITE);
    }
    board_.getSpot(0, 0)->piece = new Rook(BLACK);
    board_.getSpot(0, 7)->piece = new Rook(BLACK);
    board_.getSpot(7, 7)->piece = new Rook(WHITE);
    board_.getSpot(7, 0)->piece = new Rook(WHITE);
  };
  bool makeMove(Move move) {
    /*
    1. check CurrentTurn
    2. check CurrentSpotPiece is valid
    3. check PieceColor and CurrentPlayerColor
    4. is End place doesn't have my Piece
    5. ValidateMovement Rules
    6. ExecuteMovement (mark all Move params)
    7. Switch Turn
    */
    if (move.player != currentPlayer_) {
      throw runtime_error("Current Turn Failed");
    }
    Spot *start = move.start;
    Spot *end = move.end;

    if (start->piece != nullpt)
      throw runtime_error("CurrentSpot Piece is In-valid");
    if (move.player->color != currentPlayer_->color) {
      throw runtime_error("Current Turn Color Failed");
    }
    if (end->piece != nullptr and end->piece->color != currentPlayer_->color) {
      throw runtime_error("End Spot already has a piece of same color");
    }
    Piece *curPiece = start->piece;
    if (curPiece->canMove(board_, start, end) != true) {
      throw runtime_error("Movement Rules are invalid");
    }
    Piece *capturedPiece = end->piece;
    end->piece = piece;
    start->piece = nullptr;
    move.pieceCaptured = capturedPiece;
    move.moved = end->piece;

    currentPlayer_ = (currentPlayer_ == player2_) ? player1_ : player2_;
  };
  bool isCheck(Color color) {
    /*
    1. Find King in color
    2. Iterate in other color and see if any piece can move to king
    */
    Spot *kingSpot = nullptr;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Spot *currentSpot = board_->getSpot(i, j);
        if (currentSpot->piece->color != nullptr and
            currentSpot->piece->color == color and
            currentSpot->piece->name == "King") {
          kingSpot = currentSpot;
        }
      }
    }
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Spot *currentSpot = board_->getSpot(i, j);
        if (currentSpot->piece->color != nullptr and
            currentSpot->piece->color != color) {
          Piece *piece = currentSpot->piece;
          if (piece->canMove(board_, currentSpot, kingSpot) == true) {
            return true;
          }
        }
      }
    }
    return false;
  };
  bool isCheckMate(Color color) {
    /*
    1. isCheck(color)
    2. All same color pieces in board
        3. Make all possible moves and check isCheck()
    */
    if (!isCheck(color)) {
      return false;
    }
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        Spot *curSpot = board_->getSpot(i, j);
        if (curSpot->piece->color != color) {
          continue;
        }
        Piece *curPiece = curSpot->piece;
        for (int x = 0; x < 8; i++) {
          for (int y = 0; y < 8; y++) {
            Spot *endSpot = board_->getSpot(x, y);
            if (!curPiece->canMove(board_, curSpot, endSpot)) {
              continue;
            }
            Piece *capturePiece = endSpot->piece;
            endSpot->piece = curPiece;
            curSpot->piece = nullptr;

            if (!isCheck(color)) {
              return false;
            }
            // revert the pieces
            curSpot->piece = curPiece;
            endSpot->piece = capturePiece;
          }
        }
      }
    }
    return true;
  }
};
int main() { return 0; }