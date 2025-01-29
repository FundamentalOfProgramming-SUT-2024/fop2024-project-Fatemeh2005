#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

#define OPTIONS 4
#define setting_options 3 
#define color_options 3
#define level_options 3

void pregame(player* user) {
    while (1) {
        int selection = pregame_menu();

        if (selection == 3) {  // "Settings" option
            setting(user); 
        } else if (selection == 0) {  // "New game"
            // Start the new game here
            mvprintw(0, 0, "Starting new game...");
            refresh();
            getch();  // Placeholder logic for starting the game
            break;
        } else if (selection == 1) {  // "Resume game"
            // Resume the game logic
            mvprintw(0, 0, "Resuming game...");
            refresh();
            getch();  // Placeholder logic for resuming the game
            break;
        } else if (selection == 2) {  // "Scoreboard"
            mvprintw(0, 0, "Displaying scoreboard...");
            refresh();
            getch();  // Placeholder logic for scoreboard
        }
    }
}

int pregame_menu() {
    cbreak();
    noecho();
    curs_set(0);

    int height = 7, width = 30, start_y = 8, start_x = 15;
    WINDOW *menu_win = newwin(height, width, start_y, start_x);
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);

    char *choices[OPTIONS] = {"New game", "Resume game", "Scoreboard", "Settings"};
    int choice = 0;
    int ch;

    while (1) {
        for (int i = 0; i < OPTIONS; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 2, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }

        wrefresh(menu_win);
        ch = wgetch(menu_win);

        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + OPTIONS) % OPTIONS;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % OPTIONS;
                break;
            case '\n':
                delwin(menu_win);
                return choice;
            default:
                break;
        }
    }
}

int setting(player *user) {
    while (1) {
        int selection = setting_menu();

        if (selection == 0) {  // Difficulty level
            int level = level_choose_menu();
            user->health = 30 - (level * 5);
            user->Maxhealth = 30 - (level * 5);
            mvprintw(0, 0, "Difficulty level selected: %d", level + 1);  // Display level (1-based index)
            refresh();
            getch();  // Wait for user to acknowledge
        } else if (selection == 1) {  // Player color
            int color_selection = color_choose_menu();
            user->color = color_selection + 2;  
            mvprintw(0, 0, "Color set to %d", user->color);
            refresh();
            getch();  
        } else if (selection == 2) {  // Return to pregame menu
            break;  // Exit the settings menu
        }
    }
    refresh();
    return 1;
}

int setting_menu() {
    cbreak();
    noecho();
    curs_set(0);

    int height = 8, width = 30, start_y = 8, start_x = 15;
    WINDOW *menu_win = newwin(height, width, start_y, start_x);
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);

    char *choices[setting_options] = {"Difficulty level", "Player color", "Return to previous menu"};
    int choice = 0;
    int ch;

    while (1) {
        for (int i = 0; i < setting_options; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 2, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }

        wrefresh(menu_win);
        ch = wgetch(menu_win);

        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + setting_options) % setting_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % setting_options;
                break;
            case '\n':
                delwin(menu_win);
                return choice;
            default:
                break;
        }
    }
}

int color_choose_menu() {
    cbreak();
    noecho();
    curs_set(0);

    int height = 7, width = 30, start_y = 8, start_x = 15;
    WINDOW *menu_win = newwin(height, width, start_y, start_x);
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);

    char *choices[color_options] = {"White", "Red", "Green"};
    int choice = 0;
    int ch;

    while (1) {
        for (int i = 0; i < color_options; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 2, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }

        wrefresh(menu_win);
        ch = wgetch(menu_win);

        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + color_options) % color_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % color_options;
                break;
            case '\n':
                delwin(menu_win);
                return choice;
            default:
                break;
        }
    }
}

int level_choose_menu() {
    cbreak();
    noecho();
    curs_set(0);

    int height = 7, width = 30, start_y = 8, start_x = 15;
    WINDOW *menu_win = newwin(height, width, start_y, start_x);
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);

    char *choices[level_options] = {"Easy", "Medium", "Hard"};
    int choice = 0;
    int ch;

    while (1) {
        for (int i = 0; i < level_options; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 2, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }

        wrefresh(menu_win);
        ch = wgetch(menu_win);

        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + level_options) % level_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % level_options;
                break;
            case '\n':
                delwin(menu_win);
                return choice;
            default:
                break;
        }
    }
}
