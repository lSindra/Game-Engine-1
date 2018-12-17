#include "Game.h"

using namespace std;

int main() {
    Game game;
    
    try {
        game.run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
