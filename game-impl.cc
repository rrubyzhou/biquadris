// game-impl.cc
module game;

import <iostream>;
import <sstream>;
import player;

using namespace std;

Game::Game() : p1_{nullptr}, p2_{nullptr}, current_{nullptr} {}
Game::~Game() {}

void Game::start() {
    p1_ = make_unique<Player>("Player1");
    p2_ = make_unique<Player>("Player2");
    current_ = p1_.get();
}

void Game::restart() {
    start();
}

void Game::switchTurn() {
    if (current_ == p1_.get()) current_ = p2_.get();
    else                       current_ = p1_.get();
}

Player &Game::getCurrentPlayer() { return *current_; }
Player &Game::getOtherPlayer() { return current_ == p1_.get() ? *p2_ : *p1_; }

void Game::run() {
    if (!p1_ || !p2_) start();

    string line;

    while (true) {
        cout << "=== " << p1_->getName() << " ===\n"
                  << p1_->getBoard().toString();
        cout << "=== " << p2_->getName() << " ===\n"
                  << p2_->getBoard().toString();

        cout << current_->getName() << " > ";
        if (!getline(cin, line)) break;

        istringstream iss(line);
        string cmd;
        iss >> cmd;
        if (cmd.empty()) continue;

        bool turnEnded = current_->executeCommand(cmd);

        if (turnEnded) switchTurn();

        if (p1_->getBoard().isGameOver()) {
            cout << "Player1 has lost.\n";
            break;
        }
        if (p2_->getBoard().isGameOver()) {
            cout << "Player2 has lost.\n";
            break;
        }
    }
}
