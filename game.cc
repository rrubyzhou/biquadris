// game.cc
export module game;

import <memory>;
import <string>;
import player;

export class Game {
    std::unique_ptr<Player> p1_;
    std::unique_ptr<Player> p2_;
    Player *current_;   // non-owning pointer

public:
    Game();
    ~Game();

    void start();
    void restart();
    void run();

    void switchTurn();
    Player &getCurrentPlayer();
    Player &getOtherPlayer();
};
