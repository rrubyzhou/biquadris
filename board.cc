export module board;

import <vector>;
import <memory>;
import <string>;
import cell;
import block;

using namespace std;

/*
 * Board represents an 18x11 grid of Cells.
 
  It owns:
    - current falling block   (unique_ptr<Block>)
    - next block              (unique_ptr<Block>)
 
  Board handles:
   - placing blocks
   - moving left/right/down
   - rotating
   - dropping blocks
   - detecting collisions
   - clearing full rows
 */
export class Board {
    static const int ROWS = 18;
    static const int COLS = 11;

    vector<vector<Cell>> grid_;
    unique_ptr<Block> currentBlock_;
    unique_ptr<Block> nextBlock_;
    bool gameOver_;

    // Helpers: check bounds, occupancy, and legal block placement
    bool inBounds(int r, int c) const;
    bool cellFree(int r, int c) const;
    bool canPlace(const Block &b) const;

    // Helpers to add/remove block from grid
    void placeBlockOnGrid(const Block &b);
    void removeBlockFromGrid(const Block &b);

public:
    // Constructor: initializes empty grid
    Board();

    // Get grid for debugging or display
    const vector<vector<Cell>>& getGrid() const;

    // Is the board in a game-over state?
    bool isGameOver() const;

    // Set current block (Board takes ownership)
    void setCurrentBlock(unique_ptr<Block> b);

    // Set next block (Board takes ownership)
    void setNextBlock(unique_ptr<Block> b);

    // Access current and next blocks (non-owning)
    Block* getCurrentBlock() const;
    Block* getNextBlock() const;

    // Movement operations
    bool moveLeft();
    bool moveRight();
    bool moveDown();

    // Rotate 90 degrees clockwise
    bool rotateCW();

    // Rotate 90 degrees counter-clockwise
    bool rotateCCW();

    // Drop block to bottom; return number of cleared lines
    int drop();

    // Clear full rows and return number of rows cleared
    int clearFullRows();

    // Convert board to printable string (debug)
    string toString() const;
};
