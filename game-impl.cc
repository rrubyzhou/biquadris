// game-impl.cc
module game;

import <iostream>;
import <sstream>;
import player;

Game::Game() : p1_{nullptr}, p2_{nullptr}, current_{nullptr} {}
Game::~Game() {}

void Game::start() {
    p1_ = std::make_unique<Player>("Player1");
    p2_ = std::make_unique<Player>("Player2");
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

    std::string line;

    while (true) {
        std::cout << "=== " << p1_->getName() << " ===\n"
                  << p1_->getBoard().toString();
        std::cout << "=== " << p2_->getName() << " ===\n"
                  << p2_->getBoard().toString();

        std::cout << current_->getName() << " > ";
        if (!std::getline(std::cin, line)) break;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd.empty()) continue;

        bool turnEnded = current_->executeCommand(cmd);

        if (turnEnded) switchTurn();

        if (p1_->getBoard().isGameOver()) {
            std::cout << "Player1 has lost.\n";
            break;
        }
        if (p2_->getBoard().isGameOver()) {
            std::cout << "Player2 has lost.\n";
            break;
        }
    }
}
