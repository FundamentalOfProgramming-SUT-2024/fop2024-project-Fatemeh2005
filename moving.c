#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

extern char** map;
extern int level;
extern int ** visited;
extern room** rooms;
extern monster** monsters;

int handleinput(int input, player* user) {
    keypad(stdscr, TRUE);
    static int pressed_g = 0;
    static int fast_move_mode = 0; 
    if (input == 'M' ) {
        toggle_map_reveal(rooms);
        beneath_box( user);
        return 1;
    }
    if (fast_move_mode) {

        fast_move_mode = 0;
        int newx = user->position.x, newy = user->position.y;

        switch (input) {
            case KEY_UP: case '8':
                while ( map [newy - 1][newx] != ' '&&map [newy - 1][newx] != '_'
                &&map [newy - 1][newx] != '|'&&map [newy - 1][newx] != 'O') {
                    visited[newy-1][newx] = 1;
                    newy--;
                    mvprintw(newy, newx, "%c", map [newy][newx]);
                }
                break;
            case KEY_DOWN: case '2':
                while ( map [newy + 1][newx] != ' '&&map [newy + 1][newx] != '_'
                &&map [newy + 1][newx] != '|'&& map [newy + 1][newx] != 'O') {
                    visited [newy + 1][newx] = 1;
                    newy++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_LEFT: case '4':
                while ( map [newy][newx-1] != ' '&&map [newy ][newx-1] != '_'
                &&map [newy ][newx-1] != '|'&&map [newy ][newx-1] != 'O') {
                    visited [newy][newx-1] = 1;
                    newx--;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_RIGHT: case '6':
                while (map [newy][newx+1] != ' '&&map [newy ][newx+1] != '_'
                &&map [newy ][newx+1] != '|'&&map [newy ][newx+1] != 'O') {
                    visited [newy][newx+1]=1;
                    newx++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case '9':
                while ( map [newy-1][newx+1] != ' '&&map [newy-1 ][newx+1] != '_'
                &&map [newy-1 ][newx+1] != '|'&&map [newy-1][newx+1] != 'O') {
                    visited [newy-1][newx+1]=1;
                    newx++;
                    newy--;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case '1':
                while ( map [newy+1][newx-1] != ' '&&map [newy+1 ][newx-1] != '_'
                &&map [newy+1 ][newx-1] != '|'&&map [newy+1][newx-1] != 'O') {
                    visited [newy+1][newx-1]=1;
                    newx--;
                    newy++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case '7':
                while ( map [newy-1][newx-1] != ' '&&map [newy-1 ][newx-1] != '_'
                &&map [newy-1 ][newx-1] != '|'&&map[newy-1][newx-1] != 'O') {
                    visited [newy-1][newx-1]=1;
                    newx--;
                    newy--;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case '3':
                while ( map [newy+1][newx+1] != ' '&&map [newy+1 ][newx+1] != '_'
                &&map [newy+1][newx+1] != '|'&&map [newy+1][newx+1] != 'O') {
                    visited [newy+1][newx+1]=1;
                    newx++;
                    newy++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            default:
                return 0; 
        }
        checkposition(newy, newx, user);
        return 1;
    }

    if (input == 'f') {
        fast_move_mode = 1; 
        return 1;
    }
    if(input == 'g'){
        pressed_g = 1;
        return 1;
    }
    int newx = user->position.x, newy = user->position.y;
    switch (input) {
        case KEY_UP: case '8': newy -= 1; break;
        case KEY_DOWN: case '2': newy += 1; break;
        case KEY_LEFT: case '4': newx -= 1; break;
        case KEY_RIGHT: case '6': newx += 1; break;
        case KEY_HOME: case '7': newy -= 1; newx -= 1; break;
        case KEY_PPAGE: case '9': newy -= 1; newx += 1; break;
        case KEY_END: case '1': newy += 1; newx -= 1; break;
        case KEY_NPAGE: case '3': newy += 1; newx += 1; break;
        default: return 0;
    }
     if(pressed_g){
        pressed_g = 0;
        char space = map[newy][newx];
    if (space != ' ' && space != '_' && space != '|' && space != 'O' ) {
      
        playermove(newy, newx, user); 
    }
    return 1;}

    checkposition(newy, newx, user);
    return 1;
}
int checkposition(int newy, int newx, player* user) {
    char space = map[newy][newx];
    
    if (space != ' ' && space != '_' && space != '|' && space != 'O' ) {
        message_box();
          if (space == '$') {
            user->money += 4;   
            update_message_box("You earned 4 pieces of gold!");       
            map[newy][newx] = '.'; 
  
        }
        else if (space == 'f') {
            //user->health += 4;  
            if(user ->count_food < 5){
            update_message_box("You found some food!"); 
            user ->count_food ++;  
            map[newy][newx] = '.';  }
        }
        else if(space == 'M'){
            user ->Mweapon ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'g'){
            user ->Dweapon ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'W'){
            user ->Wweapon ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'N'){
            user ->Mweapon ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'w'){
            user ->Sweapon ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'H'){
            user ->health_potion ++;
            map [newy] [newx] = '.';
        }
        else if(space == 's'){
            user ->speed_potion ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'd'){
            user ->damage_potion ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'n'){
            user ->money +=8;
            update_message_box("This is black gold! You earned 8 pieces of gold!");
            map [newy] [newx] = '.';
        }
        if(map [user->position.y][user ->position.x] == '='){
                for(int i=rooms[2]->position.x; i<rooms[2]->position.x+rooms[2]->width; i++){
                for(int j=rooms[2]->position.y; j<rooms[2]->position.y+rooms[2]->height; j++){
                    if(visited[j][i]==0){
                        mvprintw(j, i, " ");
                    }
                }
            }
        }
        playermove(newy, newx, user);
        
    }
    beneath_box( user);
    return 1;
}
int playermove(int y, int x, player* user) {
    printw("%d", user->health);

    mvprintw(user->position.y, user->position.x, "%c", map [user->position.y][user->position.x]);
     if(map[y][x] == '='){
            for(int i=rooms[2]->position.x; i<rooms[2]->position.x+rooms[2]->width; i++){
                for(int j=rooms[2]->position.y; j<rooms[2]->position.y+rooms[2]->height; j++){
                    mvprintw(j, i,"%c", map [j][i]);
                    if (map[j][i] == '$') {
                    attron(COLOR_PAIR(1));
                    mvprintw(j, i, "$");
                    attroff(COLOR_PAIR(1));
                }
                else if(map[j][i] == 'M'){
                    const wchar_t symbol[] = L"\u2692";
                    mvaddnwstr(j, i, symbol, -1);
                }
                else if(map[j][i] == 'g'){
                     const wchar_t symbol[] = L"\U0001F5E1"; 
                    mvaddnwstr(j, i, symbol, -1);
                }
                else if(map[j][i] == 'W'){
                     const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[j][i] == 'N'){
                     const wchar_t symbol[] = L"\U000027B3"; 
                    mvaddnwstr(j, i, symbol, -1);
                }
                else if(map[j][i] == 'w'){
                    const wchar_t symbol[] = L"\U00002694";
                    mvaddnwstr(j, i, symbol, -1);
                }
                else if(map [j][i] == 'H'){
                   const wchar_t symbol[] = L"\u2716";
                    mvaddnwstr(j, i, symbol, -1); 
                }
                else if(map [j][i] == 's'){
                   const wchar_t symbol[] = L"\u2192";
                    mvaddnwstr(j, i, symbol, -1); 
                }
                else if(map [j][i] == 'd'){
                   const wchar_t symbol[] =  L"\u2297";
                    mvaddnwstr(j, i, symbol, -1); 
                }
                else if(map [j][i] == 'n'){
                   const wchar_t symbol[] = L"\U0001F6E2"; 
                mvaddnwstr(j, i, symbol, -1);
                }
                }
            }
        }


    user->position.x = x;
    user->position.y = y;

    attron(COLOR_PAIR(user ->color));
    mvprintw(user->position.y, user->position.x, "p");
    attroff(COLOR_PAIR(user ->color));
    visited [user->position.y][user->position.x]=1;
    int count_healthpotion;
    user ->count_move1++;
    user->count_move2++;
    user->count_move3++;
      
    if(user->unhungry <= 0 && user->count_move3 >= 5){
            user->health -- ;
            user->count_move3 = 0;
    }
    if(user -> unhungry>=10 && user->count_move1>=8 && user->health < user->Maxhealth){
        user->health ++;
        user->count_move2 = 0;
    }
    if(user->count_move2 > 10){
        user->unhungry --;
        
        user ->count_move1 = 0;
    }
    if(user->health<= 0){
            clear();
            printw("You Lost!");
            getch();
            endwin();
            return;
        }
    if(map [y][x] == '#'){
            for(int i = -2; i<3; i++){
                for(int j = -2; j<3; j++){
                    if(map [y+i][x+j] == '#' || map [y+i][x+j] == '+'){
                mvprintw(y+i, x+j,"%c", map [y+i][x+j]);
                visited[y+i][x+j] = 1;}
                }
            }
        }

    for (int i = 0; i < 9; i++) {
        if (user->position.x > rooms [i]->position.x && user->position.y > rooms [i]->position.y &&
            user->position.x < rooms [i]->position.x + rooms [i]->width && user->position.y < rooms [i]->position.y + rooms [i]->height)
             mark_visited_room( rooms[i]);
             print_visited(user, rooms);
             attron(COLOR_PAIR(user ->color));
                mvprintw(user->position.y, user->position.x, "p");
            attroff(COLOR_PAIR(user ->color));    
                visited [user->position.y][user->position.x]=1;
    }
    if (user->position.x > rooms [1]->position.x && user->position.y > rooms [1]->position.y &&
            user->position.x < rooms [1]->position.x + rooms [1]->width && user->position.y < rooms [1]->position.y + rooms [1]->height)
pathfindingseek( monsters[0], user);
if (user->position.x > rooms [5]->position.x && user->position.y > rooms [5]->position.y &&
            user->position.x < rooms [5]->position.x + rooms [5]->width && user->position.y < rooms [5]->position.y + rooms [5]->height)
pathfindingseek( monsters[1], user);
if (user->position.x > rooms [7]->position.x && user->position.y > rooms [7]->position.y &&
            user->position.x < rooms [7]->position.x + rooms [7]->width && user->position.y < rooms [7]->position.y + rooms [7]->height)
pathfindingseek( monsters[2], user);
    refresh();

    if (map[y][x] == '<') {
        clear();
        bkgd(COLOR_PAIR(2));

        level++;

        int terminal_height, terminal_width;
        getmaxyx(stdscr, terminal_height, terminal_width);

        for (int i = 0; i < terminal_height; i++) {
            for (int j = 0; j < terminal_width; j++) {
                map[i][j] = ' ';  
            }
        }
        for (int i = 0; i < terminal_height; i++) {
            for (int j = 0; j < terminal_width; j++) {
                visited[i][j] = 0;  
            }
        }
        rooms = mapsetup();

         mark_visited_room( rooms[0]);
         print_visited(user,rooms);

        user->position.x = rooms[0]->position.x + 1;
        user->position.y = rooms[0]->position.y + 1;

        attron(COLOR_PAIR(user ->color));
        mvprintw(user->position.y, user->position.x, "p");
        attroff(COLOR_PAIR(user ->color));
        message_box();
        update_message_box("You entered a new level!");

        refresh();
        int ch;
        while ((ch = getch()) != 'q') {
            handleinput(ch, user);
        }
        return 0;
    }
    return 1;
}
int pathfindingseek(monster* monster, player* user) {
    
    int dx = abs(monster->position.x - user->position.x);
    int dy = abs(monster->position.y - user->position.y);

    if (dx > dy) {
        if (monster->position.x > user->position.x && map[monster->position.y] [monster->position.x - 1] == '.') {
            map [monster->position.y][monster->position.x] = '.';
            monster->position.x--; 
        } else if (monster->position.x < user->position.x && map[monster->position.y] [monster->position.x + 1] == '.') {
            map [monster->position.y][monster->position.x] = '.';
            monster->position.x++; 
        }
    } else { 
        if (monster->position.y > user->position.y && map[monster->position.y - 1] [monster->position.x] == '.') {
            map [monster->position.y][monster->position.x] = '.';
            monster->position.y--; 
        } else if (monster->position.y < user->position.y && map[monster->position.y + 1] [monster->position.x] == '.') {
            map [monster->position.y][monster->position.x] = '.';
            monster->position.y++; 
        }
    }
    map [monster->position.y][monster->position.x] = monster->name;

    return 1; 
}

