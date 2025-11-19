module cell;

// constructor
Cell::Cell(int r, int c)
    : row_{r}, col_{c}, occupied_{false}, type_{' '} {}

// getters
int Cell::getRow() const { return row_; }
int Cell::getCol() const { return col_; }
bool Cell::isOccupied() const { return occupied_; }
char Cell::getType() const { return type_; }

// mutators

// mark the cell as occupied with block type t
void Cell::set(char t) {
    occupied_ = true;
    type_ = t;
}

// clear the cell (make empty)
void Cell::clear() {
    occupied_ = false;
    type_ = ' ';
}
