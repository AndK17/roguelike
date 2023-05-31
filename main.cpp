#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "roguelike/control.hpp"


void start_game()
{
    // Initialize player and enemies
    Player player(glb::roomSize / 2, glb::roomSize / 2);

    system("cls");
    // Generate map
    Map map(3);
    Map map_clear(map);

    drawGame(map, map_clear, player);
    drawStatistics(player);

    // Game loop
    while (player.getHealth() > 0) {
        char input;
        input = _getwch();
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            playGame(map, map_clear, player, input);
        } else if (input == 27) {
            std::cout << std::endl
                      << "Goodbye!" << std::endl;
            break;
        }
    }

    player.setSymbol(glb::deathPlayerSymbol);
    playGame(map, map_clear, player, '1');
    std::cout << std::endl
              << "Game over!" << std::endl;
}

int main() {
    system("cls");

    std::vector<std::string> menu_points{"Start game", "Settings", "Exit"};
    int pos = 0;
    while (1) {
        clearConsole();
        SetConsoleCursorPosition(hStdOut, makeCoord(0, 0));
        for (int i = 0; i < menu_points.size(); i++)
        {
            if (i == pos){
                SetConsoleTextAttribute(hStdOut, color_cyan);
                std::cout<<"-> ";
            }else{
                std::cout<<"   ";
            }
            std::cout<<menu_points[i]<<"\n";
            SetConsoleTextAttribute(hStdOut, color_white);
        }

        char input;
        input = _getwch();
        if (input == 'w' && pos > 0) {
            pos--;
        } else if (input == 's' && pos < 2) {
            pos++;
        }else if (input == 27) {
            std::cout << std::endl
                      << "Goodbye!" << std::endl;
            break;
        }else if (input == 13) {
            break;
        }
    }

    switch (pos)
    {
    case 0:
        start_game();
        break;
    case 1:
        break;
    case 2:
        std::cout<< "Goodbye!" << std::endl;
        break;
    }
    return 0;
}
