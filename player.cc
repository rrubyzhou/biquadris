// player.cc
export module player;

import <string>;
import <memory>;
import board;
import level;

export class Player {
    std::string name_;
    std::unique_ptr<Board> board_;
    std::unique_ptr<Level> lvl_;

    bool blindActive_;
    int extraHeavyCount_;
    int hiScore_;

public:
    Player(const std::string &name, int rows = 18, int cols = 11);
    ~Player();

    Board &getBoard();
    Level *getLevel() const;
    const std::string &getName() const;

    void setLevel(std::unique_ptr<Level> newLevel);

    // Executes canonical commands ("left", "right", etc.)
    // Returns true if the command ends the turn (i.e., drop)
    bool executeCommand(const std::string &cmd);

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
