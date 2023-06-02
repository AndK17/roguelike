#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "roguelike/control.hpp"

int len = 6;

int draw_menu(std::vector<std::string> &menu_points) {
    system("cls");
    int pos = 0;
    while (1) {
        clearConsole();
        SetConsoleCursorPosition(hStdOut, makeCoord(0, 0));
        for (int i = 0; i < menu_points.size(); i++) {
            if (i == pos) {
                SetConsoleTextAttribute(hStdOut, glb::color_cyan);
                std::cout << "-> ";
            } else {
                std::cout << "   ";
            }
            std::cout << menu_points[i] << "\n";
            SetConsoleTextAttribute(hStdOut, glb::color_white);
        }

        char input;
        input = _getwch();
        if (input == 'w' && pos > 0) {
            pos--;
        } else if (input == 's' && pos < menu_points.size() - 1) {
            pos++;
        } else if (input == 13) {
            break;
        }
    }
    return pos;
}

void start_game() {
    // Initialize player
    Player player(glb::roomSize / 2, glb::roomSize / 2);

    system("cls");
    // Generate map
    Map map(len);
    Map map_clear(map);

    drawGame(map, map_clear, player);

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

    player.setSymbol(glb::symbol["death"]);
    playGame(map, map_clear, player, '1');
    std::cout << std::endl
              << "Game over!" << std::endl;
}

void selectSymbol() {
    std::vector<std::string> select_points{"@", "+", "P", "Back"};
    int pos = draw_menu(select_points);
    switch (pos) {
    case 0:
        changePlayerSymbol('@');
        break;
    case 1:
        changePlayerSymbol('+');
        break;
    case 2:
        changePlayerSymbol('P');
        break;
    case 3:
        break;
    }
}

void selectDifficulty() {
    std::vector<std::string> select_points{"Easy", "Medium", "Hard", "Back"};
    int pos = draw_menu(select_points);
    switch (pos) {
    case 0:
        len = 3;
        break;
    case 1:
        len = 6;
        break;
    case 2:
        len = 9;
        break;
    case 3:
        break;
    }
}

void settings() {
    std::vector<std::string> settings_points{"Select player symbol", "Select difficulty", "Back"};
    int pos = draw_menu(settings_points);
    switch (pos) {
    case 0:
        selectSymbol();
        settings();
        break;
    case 1:
        selectDifficulty();
        settings();
        break;
    case 2:
        break;
    }
}

void main_menu() {
    std::vector<std::string> menu_points{"Start game", "Settings", "Exit"};
    int pos = draw_menu(menu_points);

    switch (pos) {
    case 0:
        start_game();
        main_menu();
        break;
    case 1:
        settings();
        main_menu();
        break;
    case 2:
        std::cout << std::endl << "   Goodbye!" << std::endl;
        break;
    }
}

void welcome_menu()
{
    std::cout<<"                            _ _ _        \n"
               " _ __ ___   __ _ _   _  ___| (_) | _____ \n"
               "| '__/ _ \\ / _` | | | |/ _ \\ | | |/ / _ \\ \n"
               "| | | (_) | (_| | |_| |  __/ | |   <  __/\n"
               "|_|  \\___/ \\__, |\\__,_|\\___|_|_|_|\\_\\___|\n"
               "           |___/                           \n";
    std::cout<<"\nPress any button to start";
    char input = _getwch();
}

int main() {
    system("cls");
    
    welcome_menu();

    main_menu();

    return 0;
}
