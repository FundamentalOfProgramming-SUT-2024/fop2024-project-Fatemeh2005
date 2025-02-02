#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

extern char** map;
extern int level;
extern int ** visited;
extern room** rooms;
extern monster** monsters;
extern weapon** weapons;
extern int count_damage;

int handleinput(int input, player* user, monster** monsters) {
    if(input==' '){
        hit_enemy(user, monsters);
         print_visited(user, rooms);
        monstermove(rooms, monsters, user);
        mvprintw(user->position.y, user->position.x, "p");
       
    }
    
    keypad(stdscr, TRUE);
    static int pressed_g = 0;
    static int fast_move_mode = 0; 
    if (input == 'M' ) {
        toggle_map_reveal(user, rooms);
        beneath_box( user);
        return 1;
    }
    if (fast_move_mode) {

        fast_move_mode = 0;
        int newx = user->position.x, newy = user->position.y;

switch (input) {
case KEY_UP: case '8':
        while ( map [newy - 1][newx] != ' '&&map [newy - 1][newx] != '_'&&map [newy - 1][newx] != '|'
&&map [newy - 1][newx] != 'O'&& !(monsters[0]->position.x == newx && monsters[0]->position.y==newy-1)
&& !(monsters[1]->position.x == newx && monsters[1]->position.y==newy-1)
&& !(monsters[2]->position.x == newx && monsters[2]->position.y==newy-1)
&& !(monsters[3]->position.x == newx && monsters[3]->position.y==newy-1)
&& !(monsters[4]->position.x == newx && monsters[4]->position.y==newy-1)
&& !(monsters[5]->position.x == newx && monsters[5]->position.y==newy-1)
&& !(monsters[6]->position.x == newx && monsters[6]->position.y==newy-1)) {
                    visited[newy-1][newx] = 1;
                    newy--;
                    mvprintw(newy, newx, "%c", map [newy][newx]);
                }
                break;
            case KEY_DOWN: case '2':
                while ( map [newy + 1][newx] != ' '&&map [newy + 1][newx] != '_'
                &&map [newy + 1][newx] != '|'&& map [newy + 1][newx] != 'O'
                && !(monsters[0]->position.x == newx && monsters[0]->position.y==newy+1)
                && !(monsters[1]->position.x == newx && monsters[1]->position.y==newy+1)
                && !(monsters[2]->position.x == newx && monsters[2]->position.y==newy+1)
                && !(monsters[3]->position.x == newx && monsters[3]->position.y==newy+1)
                && !(monsters[4]->position.x == newx && monsters[4]->position.y==newy+1)
                && !(monsters[5]->position.x == newx && monsters[5]->position.y==newy+1)
                && !(monsters[6]->position.x == newx && monsters[6]->position.y==newy+1)) {
                    visited [newy + 1][newx] = 1;
                    newy++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_LEFT: case '4':
                while ( map [newy][newx-1] != ' '&&map [newy ][newx-1] != '_'
                &&map [newy ][newx-1] != '|'&&map [newy ][newx-1] != 'O'
                && !(monsters[0]->position.x == newx-1 && monsters[0]->position.y==newy)
                && !(monsters[1]->position.x == newx-1 && monsters[1]->position.y==newy)
                && !(monsters[2]->position.x == newx-1 && monsters[2]->position.y==newy)
                && !(monsters[3]->position.x == newx-1 && monsters[3]->position.y==newy)
                && !(monsters[4]->position.x == newx-1 && monsters[4]->position.y==newy)
                && !(monsters[5]->position.x == newx-1 && monsters[5]->position.y==newy)
                && !(monsters[6]->position.x == newx-1 && monsters[6]->position.y==newy)) {
                    visited [newy][newx-1] = 1;
                    newx--;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_RIGHT: case '6':
                while (map [newy][newx+1] != ' '&&map [newy ][newx+1] != '_'
                &&map [newy ][newx+1] != '|'&&map [newy ][newx+1] != 'O'
                && !(monsters[0]->position.x == newx+1 && monsters[0]->position.y==newy)
                && !(monsters[1]->position.x == newx+1 && monsters[1]->position.y==newy)
                && !(monsters[2]->position.x == newx+1 && monsters[2]->position.y==newy)
                && !(monsters[3]->position.x == newx+1 && monsters[3]->position.y==newy)
                && !(monsters[4]->position.x == newx+1 && monsters[4]->position.y==newy)
                && !(monsters[5]->position.x == newx+1 && monsters[5]->position.y==newy)
                && !(monsters[6]->position.x == newx+1 && monsters[6]->position.y==newy)) {
                    visited [newy][newx+1]=1;
                    newx++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_PPAGE: case '9':
                while ( map [newy-1][newx+1] != ' '&&map [newy-1 ][newx+1] != '_'
                &&map [newy-1 ][newx+1] != '|'&&map [newy-1][newx+1] != 'O'
                && !(monsters[0]->position.x == newx+1 && monsters[0]->position.y==newy-1)
                && !(monsters[1]->position.x == newx+1 && monsters[1]->position.y==newy-1)
                && !(monsters[2]->position.x == newx+1 && monsters[2]->position.y==newy-1)
                && !(monsters[3]->position.x == newx+1 && monsters[3]->position.y==newy-1)
                && !(monsters[4]->position.x == newx+1 && monsters[4]->position.y==newy-1)
                && !(monsters[5]->position.x == newx+1 && monsters[5]->position.y==newy-1)
                && !(monsters[6]->position.x == newx+1 && monsters[6]->position.y==newy-1)) {
                    visited [newy-1][newx+1]=1;
                    newx++;
                    newy--;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_END: case '1':
                while ( map [newy+1][newx-1] != ' '&&map [newy+1 ][newx-1] != '_'
                &&map [newy+1 ][newx-1] != '|'&&map [newy+1][newx-1] != 'O'
                && !(monsters[0]->position.x == newx-1 && monsters[0]->position.y==newy+1)
                && !(monsters[1]->position.x == newx-1 && monsters[1]->position.y==newy+1)
                && !(monsters[2]->position.x == newx-1 && monsters[2]->position.y==newy+1)
                && !(monsters[3]->position.x == newx-1 && monsters[3]->position.y==newy+1)
                && !(monsters[4]->position.x == newx-1 && monsters[4]->position.y==newy+1)
                && !(monsters[5]->position.x == newx-1 && monsters[5]->position.y==newy+1)
                && !(monsters[6]->position.x == newx-1 && monsters[6]->position.y==newy+1)) {
                    visited [newy+1][newx-1]=1;
                    newx--;
                    newy++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_HOME: case '7':
                while ( map [newy-1][newx-1] != ' '&&map [newy-1 ][newx-1] != '_'
                &&map [newy-1 ][newx-1] != '|'&&map[newy-1][newx-1] != 'O'
                && !(monsters[0]->position.x == newx-1 && monsters[0]->position.y==newy-1)
                && !(monsters[1]->position.x == newx-1 && monsters[1]->position.y==newy-1)
                && !(monsters[2]->position.x == newx-1 && monsters[2]->position.y==newy-1)
                && !(monsters[3]->position.x == newx-1 && monsters[3]->position.y==newy-1)
                && !(monsters[4]->position.x == newx-1 && monsters[4]->position.y==newy-1)
                && !(monsters[5]->position.x == newx-1 && monsters[5]->position.y==newy-1)
                && !(monsters[6]->position.x == newx-1 && monsters[6]->position.y==newy-1)) {
                    visited [newy-1][newx-1]=1;
                    newx--;
                    newy--;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            case KEY_NPAGE: case '3':
                while ( map [newy+1][newx+1] != ' '&&map [newy+1 ][newx+1] != '_'
                &&map [newy+1][newx+1] != '|'&&map [newy+1][newx+1] != 'O'
                && !(monsters[0]->position.x == newx+1 && monsters[0]->position.y==newy+1)
                && !(monsters[1]->position.x == newx+1 && monsters[1]->position.y==newy+1)
                && !(monsters[2]->position.x == newx+1 && monsters[2]->position.y==newy+1)
                && !(monsters[3]->position.x == newx+1 && monsters[3]->position.y==newy+1)
                && !(monsters[4]->position.x == newx+1 && monsters[4]->position.y==newy+1)
                && !(monsters[5]->position.x == newx+1 && monsters[5]->position.y==newy+1)
                && !(monsters[6]->position.x == newx+1 && monsters[6]->position.y==newy+1)) {
                    visited [newy+1][newx+1]=1;
                    newx++;
                    newy++;
                    mvprintw(newy, newx, "%c", map [newy][newx]); 
                }
                break;
            default:
                return 0; 
        }
        checkposition(newy, newx, user, monsters);
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

    checkposition(newy, newx, user, monsters);
    return 1;
}
int checkposition(int newy, int newx, player* user, monster** monsters) {
    char space = map[newy][newx];
    
    if ((space != ' ' && space != '_' && space != '|' && space != 'O' 
    && !(monsters[0]->position.y==newy && monsters[0]->position.x == newx && monsters[0]->health>0)
    && !(monsters[1]->position.y==newy && monsters[1]->position.x == newx && monsters[1]->health>0)
    && !(monsters[2]->position.y==newy && monsters[2]->position.x == newx && monsters[2]->health>0)
    && !(monsters[3]->position.y==newy && monsters[3]->position.x == newx && monsters[3]->health>0)
    && !(monsters[4]->position.y==newy && monsters[4]->position.x == newx && monsters[4]->health>0)
    && !(monsters[5]->position.y==newy && monsters[5]->position.x == newx && monsters[5]->health>0)
    && !(monsters[6]->position.y==newy && monsters[6]->position.x == newx && monsters[6]->health>0))||
    (newy == rooms[6]->door[3].y && newx == rooms[6]->door[3].x) || (newy == rooms[6]->door[0].y && newx == rooms[6]->door[0].x)) {
        message_box();
          if (space == '$') {
            user->money += 4;  
            user->score += 8; 
            update_message_box("You earned 4 pieces of gold!", 0);       
            map[newy][newx] = '.'; 
        }
        //////////////////////////////////////////different food types
        else if (space == 'f') {
            //normal  food in rooms 0, 1, 2, 5, 8
if(checkinroom(user, rooms[0]) == 1 ||checkinroom(user, rooms[1]) == 1 ||checkinroom(user, rooms[2]) == 1 ||checkinroom(user, rooms[5]) == 1 ||checkinroom(user, rooms[8]) == 1 ){
            if(user ->count_food + user->count_perfect_food<5 ){
            update_message_box("You found some food!", 0); 
            user ->count_food ++;  
            map[newy][newx] = '.';  }
        }
        //power food in rooms 3, 7
else if(checkinroom(user, rooms[3]) == 1 ||checkinroom(user, rooms[7]) == 1 ){
        if(user ->count_food + user->count_perfect_food < 5){
            update_message_box("You found some power food! It can also increase your power temporarily", 0); 
            user ->count_perfect_food ++;
             
            map[newy][newx] = '.';  }
        }
else if(checkinroom(user, rooms[4]) == 1 ||checkinroom(user, rooms[6]) == 1 ){
        
            update_message_box("Haha it was rotten food!", 0); 
            user ->health -= 2;  
            map[newy][newx] = '.';  
        }
        }
        else if(space == 'M'){
            weapons[1]->count ++;
            map [newy] [newx] = '.';
        }
        else if(space == 'g'){
            weapons[0]->count += 10;
            map [newy] [newx] = '.';
        }
        else if(space == 'c'){
            weapons[3]->count += 8;
            map [newy] [newx] = '.';
        }
        else if(space == 't'){
            weapons[4]->count += 20;
            map [newy] [newx] = '.';
        }
        else if(space == 'w'){
            weapons[2]->count ++;
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
            user->score += 16;
            update_message_box("This is black gold! You earned 8 pieces of gold!", 0);
            map [newy] [newx] = '.';
        }
        else if(space == 'D'){
                weapons[0]->count++;
                map [newy] [newx] = '.';
                }
                ///////////normal arrow partab shode
                else if(space == 'N'){
                 weapons[4]->count++;
                 map [newy] [newx] = '.';
                }
                ///////////////magic wand partab shode
                else if(space == 'W'){
                   weapons[3]->count++;
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
    if((y == rooms[6]->door[3].y && x == rooms[6]->door[3].x) || (y == rooms[6]->door[0].y && x == rooms[6]->door[0].x))
    map[y][x] = '?';
    if(checkinroom(user, rooms[6]) == 1)    user->health --;
    /////////////////////////////////////////////////traps also alot for treasure room
    if((y == rooms[2]->position.y + 3 && x == rooms[2]->position.x + rooms[2]->width-4)
||(level == 4 && (y == rooms[4]->position.y + 1 && x == rooms[4]->position.x + rooms[4]->width-3))
||(level == 4 && (y == rooms[4]->position.y + 2 && x == rooms[4]->position.x + rooms[4]->width-4))
||(level == 4 && (y == rooms[4]->position.y + 5 && x == rooms[4]->position.x +3))){
    map [y][x] = '^';
    user->health -= 4;
    update_message_box("you fell into a trap", 0);}
    if(user->consumed_damage_potion==1){
        weapons[0]->damage = 24;      
    weapons[1]->damage = 10;
    weapons[2]->damage = 20;
    weapons[3]->damage = 30;
    weapons[4]->damage = 10;
    count_damage++;
    }
    
    if(count_damage > 10){
        user->consumed_damage_potion = 0;
    weapons[0]->damage = 12;      
    weapons[1]->damage = 5;
    weapons[2]->damage = 10;
    weapons[3]->damage = 15;
    weapons[4]->damage = 5;
    count_damage = 0;
    }
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
                else if(map[j][i] == 'c'){
                     const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(j, i, symbol, -1);
                }
                else if(map[j][i] == 't'){
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
                else if(map [j][i] == 'D'){
                const wchar_t symbol[] = L"\U0001F5E1"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                ///////////normal arrow partab shode
                else if(map [j][i] == 'N'){
                 const wchar_t symbol[] = L"\U000027B3"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                ///////////////magic wand partab shode
                else if(map [j][i] == 'W'){
                  const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(i, j, symbol, -1);
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
      
    if(user->unhungry <= 0 && user->count_move3 >= 15){
            user->health -- ;
            user->count_move3 = 0;
    }
    if(user -> unhungry>=9 && user->count_move1>=8 && user->health < user->Maxhealth){
        user->health ++;
        user->count_move1 = 0;
    }
    if(user->count_move2 > 20 && user->unhungry > 0){
        user->unhungry --;
        
        user ->count_move2 = 0;
    }
    ////////////////////////////////////////////////////////bord va bakht
    if(user->health<= 0){
            clear();
            printw("You Lost! Your score:%d     Your money:%d    ", user->score, user->money);
            updateUser("scoreboard.txt", user->username, user);
            getch();
    preallocs(user);        
    pregame2(user);
    maingame(user);
            return 0;
        }
    if(level == 4 && rooms[4]->visited == 1 && nogoldremain(rooms[4]) == 1){
        clear();
            printw("You Won! Your score:%d     Your money:%d    ", user->score, user->money);
            user->score += 40;
            updateUser("scoreboard.txt", user->username, user);
            getch();
    preallocs(user);
    pregame2(user);
    maingame(user);
            return 0;
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
    monstermove(rooms, monsters, user);
     
    refresh();
    /////////////////////////////////////////////////////next level
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
         mapsetup(rooms);

         mark_visited_room( rooms[0]);
         print_visited(user,rooms);

        user->position.x = rooms[0]->position.x + 1;
        user->position.y = rooms[0]->position.y + 1;

        attron(COLOR_PAIR(user ->color));
        mvprintw(user->position.y, user->position.x, "p");
        attroff(COLOR_PAIR(user ->color));
        message_box();
        update_message_box("You entered a new level!", 0);

        refresh();
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
        
            handleinput(ch, user, monsters);
        }
        return 0;
    }
    return 1;
}
int pathfindingseek(monster* monster, player* user) {    
    int dx = abs(monster->position.x - user->position.x);
    int dy = abs(monster->position.y - user->position.y);
    if((dx == 0 && dy == 1)||(dy == 0 && dx == 1)){
        user->health -= monster->power;
        update_message_box("The monster hit you", 1);
        return 0;
    }

        if (monster->position.x > user->position.x && map[monster->position.y] [monster->position.x - 1] == '.') {
           
            monster->position.x--; 
        } else if (monster->position.x <user->position.x && map[monster->position.y] [monster->position.x + 1] == '.') {
           
            monster->position.x++; 
        }

        else if (monster->position.y > user->position.y && map[monster->position.y - 1] [monster->position.x] == '.') {
            
            monster->position.y--; 
        } else if (monster->position.y < user->position.y && map[monster->position.y + 1] [monster->position.x] == '.') {
            
            monster->position.y++; 
        }

     dx = abs(monster->position.x - user->position.x);
     dy = abs(monster->position.y - user->position.y);
     if((dx == 0 && dy == 1)||(dy == 0 && dx == 1)){
        user->health -= monster->power;
        update_message_box("The monster hit you", 1);
        
    }
    return 1; 
}
int pathsirish(monster* monster, player* user){
    
    int dx = abs(monster->position.x - user->position.x);
    int dy = abs(monster->position.y - user->position.y);
    if((dx == 0 && dy == 1)||(dy == 0 && dx == 1)){
        user->health -= monster->power;
        update_message_box("The monster hit you", 1);
        return 0;
    }

    
        if (monster->position.x > user->position.x && (map[monster->position.y] [monster->position.x - 1] == '.'||map[monster->position.y] [monster->position.x - 1]=='+'
        ||map[monster->position.y] [monster->position.x - 1]=='#'||map[monster->position.y] [monster->position.x - 1] == '@')) {
           
            monster->position.x--; 
        } else if (monster->position.x <user->position.x && (map[monster->position.y] [monster->position.x + 1] == '.'||map[monster->position.y] [monster->position.x + 1] == '+'
        ||map[monster->position.y] [monster->position.x + 1] == '#'||map[monster->position.y] [monster->position.x + 1] == '@')) {
           
            monster->position.x++; 
        }
     
        else if (monster->position.y > user->position.y && (map[monster->position.y - 1] [monster->position.x] == '.'||map[monster->position.y - 1] [monster->position.x] == '+'
        ||map[monster->position.y - 1] [monster->position.x] == '#'||map[monster->position.y - 1] [monster->position.x] == '@')) {
            
            monster->position.y--; 
        } else if (monster->position.y < user->position.y && (map[monster->position.y + 1] [monster->position.x] == '.'||map[monster->position.y + 1] [monster->position.x] == '+'
        ||map[monster->position.y + 1] [monster->position.x] == '#'||map[monster->position.y + 1] [monster->position.x] == '@')) {
            
            monster->position.y++; 
        }

     dx = abs(monster->position.x - user->position.x);
     dy = abs(monster->position.y - user->position.y);
     if((dx == 0 && dy == 1)||(dy == 0 && dx == 1)){
        user->health -= monster->power;
        update_message_box("The monster hit you",1 );        
    }
    return 1;   
}
int checkinroom(player*user, room*room){
    for (int y = room->position.y+1; y < room->position.y + room->height; y++) {
        for (int x = room->position.x+1; x < room->position.x + room->width; x++) {
            if(user->position.x ==x && user->position.y==y) return 1;}
    }
    return 0;
}
int monsterinroom(monster* monster, room* room){
    for (int y = room->position.y+1; y < room->position.y + room->height-2; y++) {
        for (int x = room->position.x+1; x < room->position.x + room->width-2; x++) {
            if(monster->position.x ==x && monster->position.y==y) return 1;}
    }
    return 0;    
}
void hit_enemy(player* user, monster** monsters){
    //////////////////////////////Sword and Mace
    if(user->default_weapon == weapons[1] || user->default_weapon == weapons[2]){
        for(int i = 0; i<7; i++){
            if( monsters[i]->position.x == user->position.x && monsters[i]->position.y == user->position.y+1 && monsters[i]->health>0){
                monsters[i]->health -= user->default_weapon->damage;
                
                if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                else if(monsters[i]->health <= 0){
                    update_message_box("You killed the enemy!", 0);
                    user->score += (monsters[i]->power*2);
                }
            }
            else if( monsters[i]->position.x == user->position.x && monsters[i]->position.y == user->position.y-1 && monsters[i]->health>0){
                monsters[i]->health -= user->default_weapon->damage;
                
                if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                else if(monsters[i]->health <= 0){
                    update_message_box("You killed the enemy!", 0);
                    user->score += (monsters[i]->power*2);
                }
            }
            else if( monsters[i]->position.x == user->position.x+1 && monsters[i]->position.y == user->position.y && monsters[i]->health>0){
                monsters[i]->health -= user->default_weapon->damage;
                
                if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                else if(monsters[i]->health <= 0){
                    update_message_box("You killed the enemy!", 0);
                    user->score += (monsters[i]->power*2);
                }
            }
            else if( monsters[i]->position.x == user->position.x-1 && monsters[i]->position.y == user->position.y+1 && monsters[i]->health>0){
                monsters[i]->health -= user->default_weapon->damage;
                
                if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                else if(monsters[i]->health <= 0){
                    update_message_box("You killed the enemy!", 0);
                    user->score += (monsters[i]->power*2);
                }
            }
        }
    }
    ///////////////////////////////////other weapons that are long range
    else{
         user->default_weapon->count--;
        keypad(stdscr, TRUE);
        int dir;
        dir = getch();
        switch(dir){
            case KEY_UP:
                for(int i= 0; i<7; i++){
                    for(int j =1; j <= user->default_weapon->range; j++){
                        if( monsters[i]->position.x == user->position.x && monsters[i]->position.y == user->position.y-j && monsters[i]->health>0){
                            monsters[i]->health -= user->default_weapon->damage;
                            
                            if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                            else if(monsters[i]->health <= 0){
                                update_message_box("You killed the enemy!", 0);
                                user->score += (monsters[i]->power*2);
                            }
                            return;
                        }
                    }
                }
                for(int j = user->default_weapon->range; j>0; j--){
                    if(map [user->position.y-j][user->position.x] == '.'){
                        map [user->position.y-j][user->position.x] = user->default_weapon->name;
                        print_visited(user, rooms);
                            attron(COLOR_PAIR(user ->color));
                            mvprintw(user->position.y, user->position.x, "p");
                            attroff(COLOR_PAIR(user ->color));
                        return;
                    }
                }
                break;
            case KEY_DOWN:
                for(int i= 0; i<7; i++){
                    for(int j =1; j <= user->default_weapon->range; j++){
                        if( monsters[i]->position.x == user->position.x && monsters[i]->position.y == user->position.y+j && monsters[i]->health>0){
                            monsters[i]->health -= user->default_weapon->damage;
                           
                            if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                            else if(monsters[i]->health <= 0){
                                update_message_box("You killed the enemy!", 0);
                                user->score += (monsters[i]->power*2);
                            }
                        return;
                        }
                    }
                }
                for(int j = user->default_weapon->range; j>0; j--){
                    if(map [user->position.y+j][user->position.x] == '.'){
                        map [user->position.y+j][user->position.x] = user->default_weapon->name;
                        print_visited(user, rooms);
                            attron(COLOR_PAIR(user ->color));
                            mvprintw(user->position.y, user->position.x, "p");
                            attroff(COLOR_PAIR(user ->color));
                        return;
                    }
                }
                break;
            case KEY_RIGHT:
                for(int i= 0; i<7; i++){
                    for(int j =1; j <= user->default_weapon->range; j++){
                        if( monsters[i]->position.x == user->position.x+j && monsters[i]->position.y == user->position.y && monsters[i]->health>0){
                            monsters[i]->health -= user->default_weapon->damage;
                            if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                            else if(monsters[i]->health <= 0){
                                update_message_box("You killed the enemy!", 0);
                                user->score += (monsters[i]->power*2);
                            }
                            return;
                        }
                    }
                }
                for(int j = user->default_weapon->range; j>0; j--){
                    if(map [user->position.y][user->position.x+j] == '.'){
                        map [user->position.y][user->position.x+j] = user->default_weapon->name;
                        print_visited(user, rooms);
                            attron(COLOR_PAIR(user ->color));
                            mvprintw(user->position.y, user->position.x, "p");
                            attroff(COLOR_PAIR(user ->color));
                        return;
                    }
                }
                break;
            case KEY_LEFT:
                for(int i= 0; i<7; i++){
                    for(int j =1; j <= user->default_weapon->range; j++){
                        if( monsters[i]->position.x == user->position.x-j && monsters[i]->position.y == user->position.y && monsters[i]->health>0){
                            monsters[i]->health -= user->default_weapon->damage;
                            if(monsters[i]->health > 0)     update_message_box("You hit the enemy!", 0);
                            else if(monsters[i]->health <= 0){
                                update_message_box("You killed the enemy!", 0);
                                user->score += (monsters[i]->power*2);
                            }
                            return;
                        }
                    }
                }
                for(int j = user->default_weapon->range; j>0; j--){
                    if(map [user->position.y][user->position.x-j] == '.'){
                        map [user->position.y][user->position.x-j] = user->default_weapon->name;
                        print_visited(user, rooms);
                            attron(COLOR_PAIR(user ->color));
                            mvprintw(user->position.y, user->position.x, "p");
                            attroff(COLOR_PAIR(user ->color));
                        return;
                    }
                }
                break;
        }
    }
    refresh();
    beneath_box(user);
}
void monstermove(room **rooms, monster **monsters, player* user){

    for(int i = 0; i < 7; i++){
if(rooms[i+1]->visited == 1&&!(checkinroom(user, rooms[i+1]) == 0 && monsterinroom(monsters[i], rooms[i+1])==1) && (monsters[i]->name=='S'||monsters[i]->name=='U')&& monsters[i]->health>0){
      pathsirish(monsters[i], user);
    
    mvprintw(monsters[i]->position.y, monsters[i]->position.x, "%c", monsters[0]->name);    
}
else if(checkinroom(user, rooms[i+1])==1&&!(monsters[i]->name=='S'||monsters[i]->name=='U')&& monsters[i]->health>0){
    pathfindingseek(monsters[i], user);
    mvprintw(monsters[i]->position.y, monsters[i]->position.x, "%c", monsters[i]->name);}    
    }
}