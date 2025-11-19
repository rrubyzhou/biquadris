import player;
import <iostream>;

using namespace std;

int main() {
    Player p{"TestPlayer"};

    cout << p.getBoard().toString();

    p.executeCommand("right");
    p.executeCommand("down");

    cout << p.getBoard().toString();

    p.executeCommand("drop");
    cout << p.getBoard().toString();

    cout << "Score: " << p.getScore() << "\n";
}
