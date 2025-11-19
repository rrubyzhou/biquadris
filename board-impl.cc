module board;

import <sstream>;

// constructor 
Board::Board()
    : grid_(ROWS, vector<Cell>(COLS)),
      currentBlock_{nullptr},
      nextBlock_{nullptr},
      gameOver_{false}
{
    // Initialize each cell with its row/col
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            grid_[r][c] = Cell{r, c};
}

//  accessors
const vector<vector<Cell>>& Board::getGrid() const {
    return grid_;
}

bool Board::isGameOver() const {
    return gameOver_;
}


// Check if (r,c) is inside the board boundaries
bool Board::inBounds(int r, int c) const {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS;
}

// Check if cell is free and inside bounds
bool Board::cellFree(int r, int c) const {
    return inBounds(r, c) && !grid_[r][c].isOccupied();
}

// Check if a block can legally be placed
bool Board::canPlace(const Block &b) const {
    for (auto &p : b.getCells()) {
        if (!cellFree(p.first, p.second))
            return false;
    }
    return true;
}

// grid manipulation helpers

// Place a block’s coordinates on the grid
void Board::placeBlockOnGrid(const Block &b) {
    for (auto &p : b.getCells())
        grid_[p.first][p.second].set(b.getType());
}

// Remove block’s coordinates from the grid
void Board::removeBlockFromGrid(const Block &b) {
    for (auto &p : b.getCells())
        grid_[p.first][p.second].clear();
}

// block ownership/setters 

// Set current block; Board now owns b
void Board::setCurrentBlock(unique_ptr<Block> b) {
    currentBlock_ = move(b);

    if (!currentBlock_) return;

    // If the new block can't fit, game over
    if (!canPlace(*currentBlock_)) {
        gameOver_ = true;
        return;
    }

    placeBlockOnGrid(*currentBlock_);
}

// Set next block; Board owns it
void Board::setNextBlock(unique_ptr<Block> b) {
    nextBlock_ = move(b);
}

Block* Board::getCurrentBlock() const { return currentBlock_.get(); }
Block* Board::getNextBlock() const { return nextBlock_.get(); }

// moving 

bool Board::moveLeft() {
    if (!currentBlock_) return false;

    auto old = currentBlock_->getCells();
    removeBlockFromGrid(*currentBlock_);

    vector<pair<int,int>> moved;
    for (auto &p : old)
        moved.emplace_back(p.first, p.second - 1);

    currentBlock_->setCells(moved);

    if (!canPlace(*currentBlock_)) {
        currentBlock_->setCells(old);
        placeBlockOnGrid(*currentBlock_);
        return false;
    }

    placeBlockOnGrid(*currentBlock_);
    return true;
}

bool Board::moveRight() {
    if (!currentBlock_) return false;

    auto old = currentBlock_->getCells();
    removeBlockFromGrid(*currentBlock_);

    vector<pair<int,int>> moved;
    for (auto &p : old)
        moved.emplace_back(p.first, p.second + 1);

    currentBlock_->setCells(moved);

    if (!canPlace(*currentBlock_)) {
        currentBlock_->setCells(old);
        placeBlockOnGrid(*currentBlock_);
        return false;
    }

    placeBlockOnGrid(*currentBlock_);
    return true;
}

bool Board::moveDown() {
    if (!currentBlock_) return false;

    auto old = currentBlock_->getCells();
    removeBlockFromGrid(*currentBlock_);

    vector<pair<int,int>> moved;
    for (auto &p : old)
        moved.emplace_back(p.first + 1, p.second);

    currentBlock_->setCells(moved);

    // Block cannot move further; revert
    if (!canPlace(*currentBlock_)) {
        currentBlock_->setCells(old);
        placeBlockOnGrid(*currentBlock_);
        return false;
    }

    placeBlockOnGrid(*currentBlock_);
    return true;
}

// rotation

bool Board::rotateCW() {
    if (!currentBlock_) return false;

    auto old = currentBlock_->getCells();
    removeBlockFromGrid(*currentBlock_);

    // Find bounding box of the block
    int minR = 999, maxR = -1, minC = 999, maxC = -1;
    for (auto &p : old) {
        minR = min(minR, p.first);
        maxR = max(maxR, p.first);
        minC = min(minC, p.second);
        maxC = max(maxC, p.second);
    }

    int height = maxR - minR + 1;

    vector<pair<int,int>> rotated;
    for (auto &p : old) {
        int r = p.first;
        int c = p.second;

        // local coords inside bounding box
        int lr = maxR - r;
        int lc = c - minC;

        // rotated coords
        int nr = maxR - lc;
        int nc = minC + (height - 1 - lr);

        rotated.emplace_back(nr, nc);
    }

    currentBlock_->setCells(rotated);

    // Illegal rotation, revert
    if (!canPlace(*currentBlock_)) {
        currentBlock_->setCells(old);
        placeBlockOnGrid(*currentBlock_);
        return false;
    }

    placeBlockOnGrid(*currentBlock_);
    return true;
}

// drop + line clearing

// Drop block until it cannot move down
int Board::drop() {
    while (moveDown()) {}
    return clearFullRows();
}

// Remove full rows and shift everything down
int Board::clearFullRows() {
    int lines = 0;

    for (int r = ROWS - 1; r >= 0; --r) {
        bool full = true;

        // Check if row is full
        for (int c = 0; c < COLS; ++c)
            if (!grid_[r][c].isOccupied()) full = false;

        if (!full) continue;

        ++lines;

        // Shift all rows down
        for (int rr = r; rr > 0; --rr)
            for (int c = 0; c < COLS; ++c)
                grid_[rr][c] = grid_[rr-1][c];

        // Top row becomes empty
        for (int c = 0; c < COLS; ++c)
            grid_[0][c].clear();

        // re-check same row index
        ++r;
    }

    return lines;
}

// debug string

// Return a printable ASCII board representation
string Board::toString() const {
    ostringstream out;

    // Skip top 3 rows (spawn area)
    for (int r = 3; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (grid_[r][c].isOccupied())
                out << grid_[r][c].getType();
            else
                out << '.';
        }
        out << '\n';
    }

    return out.str();
}
