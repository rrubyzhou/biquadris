export module cell;

using namespace std;

/*
  Cell represents a single square on the game board.
  It stores:
  - its row and column
  - whether it is occupied
  - what block type occupies it ('I','J','L','O','S','Z','T' or ' ')
 */
export class Cell {
    int row_;
    int col_;
    bool occupied_;
    char type_;

public:
    // Constructor: creates an empty cell at (r,c)
    Cell(int r = 0, int c = 0);

    // Getters
    int getRow() const;
    int getCol() const;
    bool isOccupied() const;
    char getType() const;

    // Set this cell to a block type (mark occupied)
    void set(char t);

    // Clear this cell (make unoccupied)
    void clear();
};
