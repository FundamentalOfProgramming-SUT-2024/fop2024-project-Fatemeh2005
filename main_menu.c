#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "log_in.c"


#define MENU_OPTIONS 3

int show_menu() {
     cbreak();
     curs_set(0);
    int height = 7, width = 30, start_y = 8, start_x = 15;
    WINDOW *menu_win = newwin(height, width, start_y, start_x);
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);

    char *choices[MENU_OPTIONS] = {"Register", "Log In", "Enter as guest"};
    int choice = 0;
    int ch;
   
    while (1) {
        for (int i = 0; i < MENU_OPTIONS; i++) {
            if (i == choice) {
                wattron(menu_win, A_REVERSE);
            }
            mvwprintw(menu_win, i + 1, 2, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }

        wrefresh(menu_win);
        clear();

        ch = wgetch(menu_win);

        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + MENU_OPTIONS) % MENU_OPTIONS;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % MENU_OPTIONS;
                break;
            case '\n':
                delwin(menu_win);
                endwin();
                clear();
                return choice;
            default:
                break;
        }
    }
}
