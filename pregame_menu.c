#include <locale.h>
#include <ncurses.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

#define OPTIONS 4
#define setting_options 3 
#define color_options 3
#define level_options 3

#define MAX_LINE 100 
#define TEMP_FILE "temp.txt" 

extern char** map;
extern int level;
extern int ** visited;
extern int terminal_width;
extern int terminal_height;

typedef struct {
    char name[MAX_LINE];
    int score;
    int experience;
    int allmoney;
} User;

int pregame(player* user) {
    int selection;
    while (1) {
         selection = pregame_menu();

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
            printScoreboard("scoreboard.txt", user);
            refresh();
            getch();  // Placeholder logic for scoreboard
        }
    }
    return (selection+1);
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
void updateUser(const char *filename, char targetUser[MAX_LINE], player* user) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(TEMP_FILE, "w");

    if (!file || !temp) {
        printw("Error opening file!\n");
        return;
    }

    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[MAX_LINE];
        int number;
        int experience;
        int allmoney;
        // Trim newlines/spaces and parse data correctly
        if (sscanf(line, " %[^,], %d, %d, %d ", name, &number, &experience, &allmoney) == 4) {
            if (strcmp(name, targetUser) == 0) {
                number += user->score;  // Increase the score
                allmoney += user->money;
                experience ++;
                found = 1;
            }
            fprintf(temp, "%s, %d, %d, %d\n", name, number, experience, allmoney);
        } else {
            fprintf(temp, "%s", line);  // Keep lines that don’t match format
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(filename);  
        rename(TEMP_FILE, filename);  
       // printw("Updated successfully!\n");
    } else {
        remove(TEMP_FILE);
        //printw("User not found!\n");
    }
}
void sortUsers(User users[], int count) {
    // Sort users by score in descending order (Bubble Sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (users[j].score < users[j + 1].score) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}

void printScoreboard(const char *filename, player* user) {
    clear();
     setlocale(LC_ALL, "");
    const wchar_t cup[] = L"\U0001F3C6"; 
    const wchar_t silver_medal[] = L"\U0001F948";
    const wchar_t bronze_medal[] = L"\U0001F949";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    User users[100];
    int count = 0;
    char line[MAX_LINE];

    // Read users from file
    while (fgets(line, sizeof(line), file)) {
        if (count >= 100) break;  // Prevent overflow

        if (sscanf(line, " %[^,], %d, %d, %d ", users[count].name, &users[count].score, &users[count].experience, &users[count].allmoney) == 4) {
            count++;
        }
    }
    fclose(file);

    // Sort users by score
    sortUsers(users, count);

    // Print sorted scoreboard
    printw("\nSorted Scoreboard:\n");
    printw("    name  -  score -  experience - money gathered\n");
    printw("----------------------\n");
    for (int i = 0; i < count; i++) {
        if(i == 0){
            if(addingflash(user->username, users[i].name)==1){
                printw("-->");
            } 
            addwstr(cup);
            attron(COLOR_PAIR(1));
            
          printw(" GOAT:%s - %d - %d - %d\n", users[i].name, users[i].score, users[i].experience, users[i].allmoney);
                        attroff(COLOR_PAIR(1));
          }
        else if(i == 1){ 
            if(addingflash(user->username, users[i].name)==1){
                printw("-->");
            }
             addwstr(silver_medal); 
         attron(COLOR_PAIR(6));
         printw(" Legend:%s - %d - %d - %d\n", users[i].name, users[i].score, users[i].experience, users[i].allmoney);
         attroff(COLOR_PAIR(6));}
        else if(i==2){
            if(addingflash(user->username, users[i].name)==1){
                printw("-->");
            }
            addwstr(bronze_medal); 
         attron(COLOR_PAIR(3));
          printw("chill guy:%s - %d - %d - %d\n", users[i].name, users[i].score, users[i].experience, users[i].allmoney);
          attroff(COLOR_PAIR(3));}
        else{
            if(addingflash(user->username, users[i].name)==1){
                printw("-->");}
                 printw("       %s - %d - %d - %d\n", users[i].name, users[i].score, users[i].experience, users[i].allmoney);}
    }
    printw("----------------------\n");
}
int addingflash(char user[], char users[]) {
    return strcmp(user, users) == 0 ? 1 : 0;  // 1 if match, 0 otherwise
}
