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
monster** monsters;
weapon** weapons;
int count_damage;
int main() {
    player* user = malloc(sizeof(player));
    user ->health = 30;
    user->Maxhealth = 30;
    count_damage = 0;
    
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
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    ////////gray color
    init_color(8, 500, 500, 500); // Define gray (R,G,B values in range 0-1000)
    init_pair(6, 8, COLOR_BLACK); 

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
        else if(selection == 2){
            pregame(user);
        getch();
        clear();
        break;
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
    monsters = malloc(10* sizeof(monster*));
    for(int i = 0;i<10; i++){
        monsters[i] = malloc(sizeof(monster));
    }
     rooms = mapsetup();
     mark_visited_room( rooms[0]);
     print_visited(user, rooms);
     message_box();
    
     playersetup(user,rooms);

    int ch;
    while ((ch = getch()) != 'q') {
        
        if(ch == 'E'){
            food_menu(user);
            print_visited( user, rooms); 
            attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));            
        }
        if(ch == 'i'){
            weopon_menu(user);
            print_visited(user, rooms); 
            attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
        }
        if(ch == 'p'){
            potion_menu(user);
            print_visited(user, rooms); 
            attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
        }
        
        handleinput(ch, user,  monsters);
        
    }
    for (int i = 0; i < terminal_height; i++) {
        free(map[i]);
    }
    free(map);

    endwin();
    return 0;
}
void playersetup(player* user,room** rooms) {
    weapons = malloc(10*sizeof(weapon*));
     for(int i = 0; i<5;i++){
        weapons[i] = malloc(sizeof(weapon));
     }
    
    user->position.x = rooms[0]->position.x + 1;
    user->position.y = rooms[0]->position.y + 1;
    user ->count_food = 0;
    user ->count_perfect_food = 0;
    user ->unhungry = 10;
    user -> money = 0;
    user ->health_potion = 0;
    user ->speed_potion = 0;
    user ->damage_potion = 0;
    user->count_move1 = 0;
    user->count_move2 = 0;
    user->count_move3 = 0;
    user->consumed_damage_potion = 0;
    user->score = 0;
    
    user->default_weapon = weapons[1];
    ////////////////////////weapon initilizing
     
    weapons[0]->name = 'D';     weapons[0]->count = 0;      weapons[0]->damage = 12;      weapons[0]->range = 5;     
    weapons[1]->name = 'M';     weapons[1]->count = 1;      weapons[1]->damage = 5;      weapons[1]->range = 1;
    weapons[2]->name = 'S';     weapons[2]->count = 0;      weapons[2]->damage = 10;      weapons[2]->range = 1;
    weapons[3]->name = 'W';     weapons[3]->count = 0;      weapons[3]->damage = 15;      weapons[3]->range = 10;
    weapons[4]->name = 'N';     weapons[4]->count = 0;      weapons[4]->damage = 5;      weapons[4]->range = 5;
    attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
   
}

