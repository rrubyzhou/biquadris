module block;

// constructor
Block::Block(char t, int lvl)
    : type_{t}, levelGenerated_{lvl} {}

// getters
char Block::getType() const { return type_; }
int Block::getLevelGenerated() const { return levelGenerated_; }

const vector<pair<int,int>>& Block::getCells() const {
    return cells_;
}

// coordinate updaters

// replace the block's (r,c) coordinates
void Block::setCells(const vector<pair<int,int>>& cs) {
    cells_ = cs;
}

// add an (r,c) coordinate
void Block::addCell(int r, int c) {
    cells_.emplace_back(r, c);
}
