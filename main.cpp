#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "roguelike/control.hpp"

int len = 6;

void show_screen(std::string screen) {
    clearConsole();
    std::cout << screen;
    std::cout << "\nPress any button to continue";
    char input = _getwch();
}

int draw_menu(std::vector<std::string> &menu_points) {
    system("cls");
    int pos = 0;
    while (1) {
        clearConsole();
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
    Player player(glb::roomSize / 2, glb::roomSize / 2);

    system("cls");

    Map map(len);
    Map map_clear(map);

    drawGame(map, map_clear, player);

    bool is_win{false};
    char input;
    while (player.getHealth() > 0) {
        input = _getwch();
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            is_win = playGame(map, map_clear, player, input);
            if (is_win) {
                show_screen(screens::you_win);
                break;
            } 
        } else if (input == 27) {
            break;
        }
    }
    if (!is_win && input != 27) show_screen(screens::you_died);
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
        len = 9;
        break;
    case 1:
        len = 6;
        break;
    case 2:
        len = 3;
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
        std::cout << std::endl
                  << "   Goodbye!" << std::endl;
        break;
    }
}

int main() {
    system("cls");

    show_screen(screens::roguelike);

    main_menu();

    return 0;
}
