#include <iostream>
#include "GameManager.h"

int main() {
    GameManager game;
    bool running = true;

    while (running) {
        game.startDay();

        int choice = game.selectMode();
        running = game.executeAction(choice);

        if (running)  game.endDay();
    }

    std::cout << "Thank you for playing!\n";
    return 0;
}
