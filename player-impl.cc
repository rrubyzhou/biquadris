// player-impl.cc
#include "player.cc"
#include "level-impl.cc"   // includes Level0 implementation
#include <utility>

Player::Player(const std::string &name, int rows, int cols)
    : name_{name},
      board_{std::make_unique<Board>(rows, cols)},
      lvl_{std::make_unique<Level0>()},
      blindActive_{false},
      extraHeavyCount_{0},
      hiScore_{0}
{
    // Spawn first block from current level
    Block b = lvl_->generateBlock();
    board_->placeNewBlock(b);
}

Player::~Player() {}

Board &Player::getBoard() { return *board_; }
Level *Player::getLevel() const { return lvl_.get(); }
const std::string &Player::getName() const { return name_; }

void Player::setLevel(std::unique_ptr<Level> newLevel) {
    lvl_ = std::move(newLevel);
}

// Execute one command from CommandInterpreter
bool Player::executeCommand(const std::string &cmd) {
    if (cmd == "left") {
        board_->moveLeft();
        return false;
    }
    if (cmd == "right") {
        board_->moveRight();
        return false;
    }
    if (cmd == "down") {
        board_->moveDown();
        return false;
    }
    if (cmd == "clockwise") {
        board_->rotateClockwise();
        return false;
    }
    if (cmd == "counterclockwise") {
        board_->rotateCounterClockwise();
        return false;
    }

    if (cmd == "drop") {
        int cleared = board_->dropCurrentBlock();

        // Next block
        Block nb = lvl_->generateBlock();
        bool ok = board_->placeNewBlock(nb);

        // Blind always clears after drop (UML pattern)
        clearBlind();

        // Hi-score update
        if (board_->getScore() > hiScore_) hiScore_ = board_->getScore();

        // If cannot place → game over, but Game handles that
        return true;
    }

    if (cmd == "restart") {
        board_->reset();
        board_->placeNewBlock(lvl_->generateBlock());
        blindActive_ = false;
        extraHeavyCount_ = 0;
        return false;
    }

    // Unknown command — ignored
    return false;
}

void Player::applyBlind() { blindActive_ = true; }
void Player::clearBlind() { blindActive_ = false; }
void Player::applyHeavy() { extraHeavyCount_++; }

void Player::applyForce(const Block &b) {
    // Force next block — for now, replace spawn block
    board_->placeNewBlock(b);
}

// Level transitions — real project will replace Level0 with Level1/2/3/4
void Player::levelUp() {
    lvl_ = std::make_unique<Level0>(); // placeholder
}
void Player::levelDown() {
    lvl_ = std::make_unique<Level0>(); // placeholder
}

int Player::getScore() const { return board_->getScore(); }
int Player::getHiScore() const { return hiScore_; }
