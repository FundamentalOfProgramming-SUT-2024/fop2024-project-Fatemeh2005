#ifndef MAP_H
#define MAP_H

#include <ncurses.h>

typedef struct position {
    int x;
    int y;
} position;

typedef struct room {
    int level;
    position position;
    int height;
    int width;
    position door[4];
} room;

typedef struct player {
    int Maxhealth;
    int color;
    position position;
    int health;
    int count_move1;//rythm for addition to health
    int count_move2;//rythm for decrease of unhungry
    int count_move3;//rhytm of decrese of health due tp not eating
    int count_food;
    int unhungry;
    int money;
    int Mweapon, Dweapon, Wweapon, Nweapon, Sweapon;
    int health_potion, speed_potion, damage_potion;
    int consumed_health_potion;
    //int score
} player;
typedef struct monster {
    position position;
    char name;
    int health;
    int power;
}monster;
int mark_visited_room(room* room);
int print_visited(player* user,room** rooms);
room** mapsetup();                    
room* createroom(int i, int y, int x, int height, int width);  
int drawroom(int k,room* room);              
void connect_rooms_right(room* room1, room* room2); 
void connect_rooms_top(room* room1, room* room2);    
void playersetup(player* user,room** rooms);       
int handleinput(int input, player* user);
int checkposition(int newy, int newx, player* user);   
int playermove(int y, int x, player* user);     
void toggle_map_reveal(room**rooms);    
void update_message_box(const char* message);
void message_box();
int show_menu();
int sign_in(player* user);
int log_in(player* user);
void beneath_box(player * user);
void food_menu();
void weopon_menu(player* user);
void potion_menu(player* user);
int setting(player *user);
int pregame_menu();
int setting_menu();
int color_choose_menu();
int level_choose_menu();
void pregame(player* user);
int moveMonsters(player* user, monster** monsters);
int pathfindingseek(monster* monsters, player* user);
#endif