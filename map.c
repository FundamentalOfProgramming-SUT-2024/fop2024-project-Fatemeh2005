#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "map.h"

extern char** map;
extern int level;
extern int ** visited;
extern monster** monsters;
extern weapon** weapons;

room** mapsetup() {

    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);

    int cell_height = terminal_height / 3;
    int cell_width = terminal_width / 3;

    int min_width = 7, max_width = cell_width - 8;
    int min_height = 7, max_height = cell_height - 8;
    int margin = 4;

    int room_count = 9;
    room** rooms = malloc(sizeof(room*) * room_count);

    for (int i = 0; i < room_count; i++) {
        int region_y = (i / 3) * cell_height;
        int region_x = (i % 3) * cell_width;

        int width = min_width + rand() % (max_width - min_width + 1);
        int height = min_height + rand() % (max_height - min_height + 1);

        int x = region_x + margin + rand() % (cell_width - width - 2 * margin + 1);
        int y = region_y + margin + rand() % (cell_height - height - 2 * margin + 1);

        rooms[i] = createroom( i,y, x, height, width);
    }

    connect_rooms_right(rooms[0], rooms[1]);
    connect_rooms_right(rooms[1], rooms[2]);
    connect_rooms_right(rooms[3], rooms[4]);
    connect_rooms_right(rooms[4], rooms[5]);
    connect_rooms_right(rooms[6], rooms[7]);
    connect_rooms_top(rooms[0], rooms[3]);
    connect_rooms_top(rooms[3], rooms[6]);
    connect_rooms_top(rooms[4], rooms[7]);
    connect_rooms_top(rooms[5], rooms[8]);

    if (level != 4) {
        int random_stair = 6 + rand() % 3;
        map[rooms[random_stair]->position.y + rooms[random_stair]->height - 3][rooms[random_stair]->position.x + rooms[random_stair]->width - 3] = '<';
    }
    map[rooms[4]->door[1].y][rooms[4]->door[1].x] = '@';
    map[rooms[4]->position.y+rooms[4]->height-1][rooms[4]->position.x+rooms[4]->width-1] = '&';

    //generating_monsters( rooms);

    return rooms;
}
// tabaghe akhar teme 5 omin otaghesho ganj mikonam
room* createroom(int i,int y, int x, int height, int width) {
    room* newroom = malloc(sizeof(room));

    newroom->position.x = x;
    newroom->position.y = y;
    newroom->height = height;
    newroom->width = width;
    newroom->visited = 0;

    newroom->door[0].x = x + rand() % (width - 2) + 1;
    newroom->door[0].y = y;
    newroom->door[1].x = x + rand() % (width - 2) + 1;
    newroom->door[1].y = y + height - 1;
    newroom->door[2].x = x;
    newroom->door[2].y = y + rand() % (height - 2) + 1;
    newroom->door[3].x = x + width - 1;
    newroom->door[3].y = y + rand() % (height - 2) + 1;
    
    drawroom(i, newroom);
    
    return newroom;
}

int drawroom(int k, room* room) {
   
    for (int x = 0; x < room->width; x++) {
        map[room->position.y][room->position.x + x] = '_';
        map[room->position.y + room->height - 1][room->position.x + x] = '_';
    }

    for (int y = 1; y < room->height - 1; y++) {
        map[room->position.y + y][room->position.x] = '|';
        map[room->position.y + y][room->position.x + room->width - 1] = '|';
        for (int x = 1; x < room->width - 1; x++) {
            map[room->position.y + y][room->position.x + x] = '.';
        }
    }
    if(k >= 6 && k<= 8){
        map[room->door[0].y][room->door[0].x] = '+';
    }
    else if(k == 4 || k == 5){
    for (int i = 1; i < 4; i++) {
        map[room->door[i].y][room->door[i].x] = '+';
    }
    if(k==5)  map[room->door[3].y][room->door[3].x] = '|';  
    }
    else if(k == 1|| k==2){
        for (int i = 2; i < 4; i++) {
        map[room->door[i].y][room->door[i].x] = '+';
    }
    if(k==2)  map[room->door[3].y][room->door[3].x] = '|'; 
    }
    else if(k == 0){
        map[room->door[1].y][room->door[1].x] = '+';
        map[room->door[3].y][room->door[3].x] = '+';
    }
    else if(k == 3){
        for (int i = 0; i < 4; i++) {
        map[room->door[i].y][room->door[i].x] = '+';
    }
    map[room->door[2].y][room->door[2].x] = '|';
    }
    if(k == 1){
        map[room->door[3].y-1][room->door[3].x] = '=';
    }
    ////////////////////////////////////did this for hidden door
    if(k == 6)      {map[room->door[3].y][room->door[3].x] = '|';   map[room->door[0].y][room->door[0].x] = '_';}
    if(k == 7)      map[room->door[2].y][room->door[2].x] = '+';
    int random_number = 2 + rand() % 3;
    int random_weapon = rand() % 5;
    map[room->position.y + random_number][room->position.x + random_number] = 'O';

    int food_not = rand() % 3;
    if (food_not == 1) {
        map[room->position.y + random_number + 1][room->position.x + random_number + 1] = 'f';
    }

    if (food_not == 2 &&(random_weapon==0||random_weapon==1||random_weapon==2||random_weapon==3)) {
        attron(COLOR_PAIR(1));
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = '$';
        attroff(COLOR_PAIR(1));
    }
    if (food_not == 2 && random_weapon==4) {
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = 'n';
        }
    if(food_not == 0 && random_number% 2 == 0){
        switch (random_weapon){
        case 0:
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = 'M';
        break;
        case 1:
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = 'g';
        break;
        case 2:
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = 'c';
        break;
        case 3:
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = 't';
        break;
        case 4:
        map [room->position.y + random_number + 1][room->position.x + random_number + 1] = 'w';
        break;
         }   
    }
int random_potion = rand() % 3;
    if(random_weapon == 0){
        switch (random_potion){
        case 0:
        map [room->position.y + random_number ][room->position.x + random_number ] = 'H';
        break;
        case 1:
        map [room->position.y + random_number ][room->position.x + random_number ] = 's';
        break;
        case 2:
        map [room->position.y + random_number ][room->position.x + random_number ] = 'd';
        break;}
    }
    if(k==1){
        if(random_weapon==0){
           
            monsters [0]->name = 'D';   monsters[0]->health = 5;    monsters[0]->power = 1;
        }
        else if(random_weapon==1 ){
                
                monsters [0]->name = 'S';   monsters [0]->health= 20;    monsters[0]->power = 3;  
        }
        else if(random_weapon == 4){
            
                monsters [0]->name = 'G';    monsters [0]->health= 15;    monsters[0]->power = 2;
        }
        else if(random_weapon==2) {
       monsters [0]->name = 'U';    monsters [0]->health= 30;    monsters[0]->power = 4;}
        else if (random_weapon==3) {
       monsters [0]->name = 'F';    monsters[0]->health = 10;    monsters[0]->power = 2;}
       monsters[0]->position.x=room->position.x + room->width-2;monsters[0]->position.y=room->position.y + room->height-2;
    }
    if(k==5){
        if(random_weapon==0){
            
            monsters [1]->name = 'D';   monsters[1]->health = 5;    monsters[1]->power = 1;
        }
        else if(random_weapon==1 ){
                
                monsters [1]->name = 'S';   monsters [1]->health= 20;    monsters[1]->power = 3;  
        }
        else if(random_weapon==4){
               
                monsters [1]->name = 'G';   monsters [1]->health= 15;    monsters[1]->power = 2;
        }
        else if(random_weapon==2) {
       monsters [1]->name = 'U';    monsters [1]->health= 30;    monsters[1]->power = 4;}
        else if (random_weapon==3) {
       monsters [1]->name = 'F';    monsters[1]->health = 10;    monsters[1]->power = 2;}
       monsters[1]->position.x=room->position.x + room->width-2;monsters[1]->position.y=room->position.y + room->height-2;
    }
    if(k==7){
        if(random_weapon==0){
          
            monsters [2]->name = 'D';   monsters[2]->health = 5;    monsters[2]->power = 1;
        }
        else if(random_weapon==1 ){
             
                monsters [2]->name = 'S';   monsters [2]->health= 20;    monsters[2]->power = 3;
        }
        else if(random_weapon==4){
             
                monsters [2]->name = 'G';   monsters [2]->health= 15;    monsters[2]->power = 2;
        }
        else if(random_weapon==2) {
       monsters [2]->name = 'U';    monsters [2]->health= 30;    monsters[2]->power = 4;}
        else if (random_weapon==3) {
       monsters [2]->name = 'F';    monsters[2]->health = 10;    monsters[2]->power = 2;}
    monsters [2]->position.x=room->position.x + room->width-2;monsters [2]->position.y=room->position.y + room->height-2;
    }
    refresh();
    return 1;
}

void connect_rooms_right(room* room1, room* room2) {
    int start_x = room1->door[3].x;
    int start_y = room1->door[3].y;
    int end_x = room2->door[2].x - 1;  
    int end_y = room2->door[2].y;
    int y = start_y;
    int x = start_x;

    if (start_y != end_y) {
        while (x != end_x) {
            x += (end_x > start_x) ? 1 : -1;
            map[start_y][x] = '#';
        }

        while (y != end_y) {
            y += (end_y > start_y) ? 1 : -1; 
            map[y][end_x] = '#';
        }
    } else {
        map[start_y][start_x + 1] = '#';
        map[start_y + 1][start_x + 1] = '#';
        start_x++; start_y++;

        while (x != end_x) {
            x += (end_x > start_x) ? 1 : -1;
            map[start_y][x] = '#';
        }

        map[start_y - 1][end_x] = '#';
    }
}

void connect_rooms_top(room* room1, room* room2) {
    int start_x = room1->door[1].x; 
    int start_y = room1->door[1].y;
    int end_x = room2->door[0].x;  
    int end_y = room2->door[0].y - 1;
    int x = start_x;
    int y = start_y;

    if (start_x != end_x) {
        while (y != end_y) {
            y += (end_y > start_y) ? 1 : -1; 
            map[y][start_x] = '#';
        }

        while (x != end_x) {
            x += (end_x > start_x) ? 1 : -1;
            map[end_y][x] = '#';
        }
    } else {
        map[start_y + 1][start_x] = '#';
        map[start_y + 1][start_x + 1] = '#';
        start_x++; start_y++;

        while (y != end_y) {
            y += (end_y > start_y) ? 1 : -1; 
            map[y][start_x] = '#';
        }

        map[end_y][start_x - 1] = '#';
    }  
}
int print_visited(player*user,room** rooms) {
    
    setlocale(LC_ALL, "");
    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);
    for (int i = 0; i < terminal_height; i++) {
        for (int j = 0; j < terminal_width; j++) {
            if (visited[i][j] == 1) {
                if (map[i][j] == '$') {
                    attron(COLOR_PAIR(1));
                    mvprintw(i, j, "$");
                    attroff(COLOR_PAIR(1));
                }
                else if(map[i][j] == 'M'){
                    const wchar_t symbol[] = L"\u2692";
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 'g'){
                     const wchar_t symbol[] = L"\U0001F5E1"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 'c'){
                     const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 't'){
                     const wchar_t symbol[] = L"\U000027B3"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 'w'){
                    const wchar_t symbol[] = L"\U00002694";
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map [i][j] == 'H'){
                   const wchar_t symbol[] = L"\u2716";
                    mvaddnwstr(i, j, symbol, -1); 
                }
                else if(map [i][j] == 's'){
                   const wchar_t symbol[] = L"\u2192";
                    mvaddnwstr(i, j, symbol, -1); 
                }
                else if(map [i][j] == 'd'){
                   const wchar_t symbol[] =  L"\u2297";
                    mvaddnwstr(i, j, symbol, -1); 
                }
                else if(map [i][j] == 'n'){
                   const wchar_t symbol[] = L"\U0001F6E2"; 
                mvaddnwstr(i, j, symbol, -1);
                }
                /////////dagger partab shode
                else if(map [i][j] == 'D'){
                const wchar_t symbol[] = L"\U0001F5E1"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                ///////////normal arrow partab shode
                else if(map [i][j] == 'N'){
                 const wchar_t symbol[] = L"\U000027B3"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                ///////////////magic wand partab shode
                else if(map [i][j] == 'W'){
                  const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(i >= rooms[6]->position.y && j >= rooms[6]->position.x&&
                        i < rooms[6]->height+rooms[6]->position.y&&j<rooms[6]->width+rooms[6]->position.x) {
                attron(COLOR_PAIR(4));
                mvprintw(i, j, "%c", map[i][j]);
                attroff(COLOR_PAIR(4));
    }
                
                else {
if (level == 4 && i >= rooms[4]->position.y && j >= rooms[4]->position.x&&
i < rooms[4]->height+rooms[4]->position.y&&j<rooms[4]->width+rooms[4]->position.x) {
    attron(COLOR_PAIR(1));
    mvprintw(i, j, "%c", map[i][j]);
    attroff(COLOR_PAIR(1));
    
}
           else     mvprintw(i, j, "%c", map[i][j]);
                }
            }
        }
    }
    
    refresh();
    return 1;
}
int mark_visited_room(room* room) {
    for (int y = room->position.y; y < room->position.y + room->height; y++) {
        for (int x = room->position.x; x < room->position.x + room->width; x++) {
            if(map [y][x] == '$'){
                attron(COLOR_PAIR(1));
            }
           visited[y][x] = 1;
            attroff(COLOR_PAIR(1));
            room->visited = 1;
        }  
    }           
    refresh();
    return 1;    
}
void toggle_map_reveal(player* user,room** rooms) {
    static int map_revealed = 0; // Tracks whether the map is currently revealed
    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);
    if (!map_revealed){
        for (int i = 0; i < terminal_height; i++) {
        for (int j = 0; j < terminal_width; j++) { 
            if(visited[i][j] == 0){
                if (map[i][j] == '$') {
                    attron(COLOR_PAIR(1));
                    mvprintw(i, j, "$");
                    attroff(COLOR_PAIR(1));
                }
                else if(map[i][j] == 'M'){
                    const wchar_t symbol[] = L"\u2692";
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 'g'){
                     const wchar_t symbol[] = L"\U0001F5E1"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 'c'){
                     const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 't'){
                     const wchar_t symbol[] = L"\U000027B3"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map[i][j] == 'w'){
                    const wchar_t symbol[] = L"\U00002694";
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(map [i][j] == 'H'){
                   const wchar_t symbol[] = L"\u2716";
                    mvaddnwstr(i, j, symbol, -1); 
                }
                else if(map [i][j] == 's'){
                   const wchar_t symbol[] = L"\u2192";
                    mvaddnwstr(i, j, symbol, -1); 
                }
                else if(map [i][j] == 'd'){
                   const wchar_t symbol[] =  L"\u2297";
                    mvaddnwstr(i, j, symbol, -1); 
                }
                else if(map [i][j] == 'n'){
                   const wchar_t symbol[] = L"\U0001F6E2"; 
                mvaddnwstr(i, j, symbol, -1);
                }
                /////////dagger partab shode
                else if(map [i][j] == 'D'){
                const wchar_t symbol[] = L"\U0001F5E1"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                ///////////normal arrow partab shode
                else if(map [i][j] == 'N'){
                 const wchar_t symbol[] = L"\U000027B3"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                ///////////////magic wand partab shode
                else if(map [i][j] == 'W'){
                  const wchar_t symbol[] = L"\U00002726"; 
                    mvaddnwstr(i, j, symbol, -1);
                }
                else if(i >= rooms[6]->position.y && j >= rooms[6]->position.x&&
                        i < rooms[6]->height+rooms[6]->position.y&&j<rooms[6]->width+rooms[6]->position.x) {
                attron(COLOR_PAIR(4));
                mvprintw(i, j, "%c", map[i][j]);
                attroff(COLOR_PAIR(4));
    }
                else {
if (level == 4 && i >= rooms[4]->position.y && j >= rooms[4]->position.x&&
i < rooms[4]->height+rooms[4]->position.y&&j<rooms[4]->width+rooms[4]->position.x) {
    attron(COLOR_PAIR(1));
    mvprintw(i, j, "%c", map[i][j]);
    attroff(COLOR_PAIR(1));
    
}
           else     mvprintw(i, j, "%c", map[i][j]);
                }

            }    
        }
    }
}        
    else{
        for (int i = 3; i < terminal_height; i++) {
        for (int j = 0; j < terminal_width; j++) { 
            if(visited[i][j] == 0)  mvprintw(i, j, " ");       
        }
    }        
    }    
    map_revealed = !map_revealed; // Toggle the state
    refresh();
}
void message_box(){
    int terminal_height, terminal_width;
    getmaxyx(stdscr, terminal_height, terminal_width);

    for(int i = 1; i < terminal_width;i++){
        mvprintw(1,i," ");
    }
}
void update_message_box(const char* message) {
    
    mvprintw(1, 2, "%s", message);

    refresh();
}
void beneath_box(player * user){
    // other necessary information will later be added
        int terminal_height, terminal_width;
        getmaxyx(stdscr, terminal_height, terminal_width);
        mvprintw(terminal_height- 5, 4, "Money : %d", user -> money);
        mvprintw(terminal_height- 5, 20, "Health : %d", user ->health);
        mvprintw(terminal_height- 5, 40, "Score : %d", user ->score);
}
