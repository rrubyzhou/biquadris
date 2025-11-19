// player.cc
export module player;

import <string>;
import <memory>;
import board;
import level;

using namespace std;

export class Player {
    string name_;
    unique_ptr<Board> board_;
    unique_ptr<Level> lvl_;

    bool blindActive_;
    int extraHeavyCount_;
    int hiScore_;

public:
    Player(const string &name);
    ~Player();

    Board &getBoard();
    Level *getLevel() const;
    const string &getName() const;

    void setLevel(unique_ptr<Level> newLevel);

    // Executes canonical commands ("left", "right", etc.)
    // Returns true if the command ends the turn (i.e., drop)
    bool executeCommand(const string &cmd);

    // Effects
    void applyBlind();
    void clearBlind();
    void applyHeavy();
    void applyForce(const Block &b);

    // Level adjustments
    void levelUp();
    void levelDown();

    int getScore() const;
    int getHiScore() const;
};
