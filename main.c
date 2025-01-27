#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map.h"
#include "moving.c"
#include "main_menu.c"
#include "game_menus.c"

static int map_revealed = 0;
char** map;
int level;
 room** rooms;
int ** visited;
int main() {
    player* user = malloc(sizeof(player));
    
    level = 1;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    srand(time(NULL));
    
    curs_set(FALSE);
     start_color(); 
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK); 
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    bkgd(COLOR_PAIR(2)); 
    refresh;
    while (1) {
        int selection = show_menu();

        if (selection == 0) {
            int enter = sign_in(user);
            if(enter){
                break;
            }  
            
        } else if (selection == 1) {
            int enter =log_in(user);   
            if(enter){
                break;
            }
        }
    }
    noecho();

    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);
    map = (char**)malloc(terminal_height * sizeof(char*));
    for (int i = 0; i < terminal_height; i++) {
        map[i] = (char*)malloc(terminal_width * sizeof(char));
        memset(map[i], ' ', terminal_width);
    }
    visited = (int**)malloc(terminal_height * sizeof(int*));
    for (int i = 0; i < terminal_height; i++) {
        visited[i] = (int*)malloc(terminal_width * sizeof(int));
    }
    for (int i = 0; i < terminal_height; i++) {
        for (int j = 0; j < terminal_width; j++) { 
            visited[i][j] = 0;}
    }
     rooms = mapsetup();
     mark_visited_room( rooms[0]);
     print_visited( rooms);
     message_box();
    
     playersetup(user,rooms);

    int ch;
    while ((ch = getch()) != 'q') {
        
        if(ch == 'E'){
            food_menu(user);
            print_visited( rooms); 
            attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));            
        }
        if(ch == 'i'){
            weopon_menu(user);
            print_visited( rooms); 
            attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
        }
        if(ch == 'p'){
            potion_menu(user);
            print_visited( rooms); 
            attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
        }
        handleinput(ch, user);
    }
    for (int i = 0; i < terminal_height; i++) {
        free(map[i]);
    }
    free(map);

    endwin();
    return 0;
}
void playersetup(player* user,room** rooms) {
    
    user->position.x = rooms[0]->position.x + 1;
    user->position.y = rooms[0]->position.y + 1;
    user ->count_food = 0;
    user ->hungry = 10;
    user -> money = 0;
    user ->Mweapon = 1;
    user -> Dweapon = 0;
    user -> Wweapon = 0;
    user -> Nweapon = 0;
    user -> Sweapon = 0;
    user ->health_potion = 0;
    user ->speed_potion = 0;
    user ->damage_potion = 0;
    user->count_move = 0;
    attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
   
}

