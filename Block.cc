export module block;

import <vector>;
import <utility>;

using namespace std;

/*
  Block stores:
    - its type (I/J/L/O/S/Z/T)
    - the level where it was generated (for scoring)
    - its 4 (row,col) coordinates on the board
   Block does not move itself. Board modifies its coordinates when moving/rotating.
 */
export class Block {
    char type_;
    int levelGenerated_;
    vector<pair<int,int>> cells_;

public:
    // Constructor: type and level it was created in
    Block(char t, int lvl);

    // Get the block's type
    char getType() const;

    // Get the level this block was generated in
    int getLevelGenerated() const;

    // Get the current list of (r,c) coordinates this block occupies
    const vector<pair<int,int>>& getCells() const;

    // Replace the block's coordinates
    void setCells(const vector<pair<int,int>>& cs);

    // Add an (r,c) coordinate to the block
    void addCell(int r, int c);
};
