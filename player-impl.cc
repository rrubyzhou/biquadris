// player-impl.cc
module player;

import <utility>;
import board;
import level;

using namespace std

Player::Player(const string &name, int rows, int cols)
    : name_{name},
      board_{make_unique<Board>(rows, cols)},
      lvl_{make_unique<Level0>()},
      blindActive_{false},
      extraHeavyCount_{0},
      hiScore_{0}
{
    Block b = lvl_->generateBlock();
    board_->placeNewBlock(b);
}

Player::~Player() {}

Board &Player::getBoard() { return *board_; }
Level *Player::getLevel() const { return lvl_.get(); }
const string &Player::getName() const { return name_; }

void Player::setLevel(unique_ptr<Level> newLevel) {
    lvl_ = move(newLevel);
}

bool Player::executeCommand(const string &cmd) {
    if (cmd == "left")            { board_->moveLeft(); return false; }
    if (cmd == "right")           { board_->moveRight(); return false; }
    if (cmd == "down")            { board_->moveDown(); return false; }
    if (cmd == "clockwise")       { board_->rotateClockwise(); return false; }
    if (cmd == "counterclockwise"){ board_->rotateCounterClockwise(); return false; }

    if (cmd == "drop") {
        board_->dropCurrentBlock();
        Block nb = lvl_->generateBlock();
        bool ok = board_->placeNewBlock(nb);
        clearBlind();
        if (board_->getScore() > hiScore_) hiScore_ = board_->getScore();
        return true; // drop always ends turn
    }

    if (cmd == "restart") {
        board_->reset();
        board_->placeNewBlock(lvl_->generateBlock());
        blindActive_ = false;
        extraHeavyCount_ = 0;
        return false;
    }

    return false; // ignore unknown command
}

void Player::applyBlind() { blindActive_ = true; }
void Player::clearBlind() { blindActive_ = false; }
void Player::applyHeavy() { extraHeavyCount_++; }

void Player::applyForce(const Block &b) {
    board_->placeNewBlock(b);
}

void Player::levelUp()   { lvl_ = make_unique<Level0>(); }
void Player::levelDown() { lvl_ = make_unique<Level0>(); }

int Player::getScore() const { return board_->getScore(); }
int Player::getHiScore() const { return hiScore_; }
