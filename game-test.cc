import game;

int main() {
    Game g;
    g.start();

    // Fake input via direct calls (bypassing run loop)
    g.getCurrentPlayer().executeCommand("right");
    g.getCurrentPlayer().executeCommand("down");
    g.getCurrentPlayer().executeCommand("drop");

    g.switchTurn();
    g.getCurrentPlayer().executeCommand("left");

    // Print both boards
    std::cout << g.getOtherPlayer().getBoard().toString();
    std::cout << g.getCurrentPlayer().getBoard().toString();

    return 0;
}
