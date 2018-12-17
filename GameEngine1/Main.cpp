#include <stdio.h>
#include "GameLogic/GameLogic.h"

using namespace Game;
using namespace std;

int main() {
    GameLogic gameLogic =* new GameLogic();

    try {
        gameLogic.Run();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
