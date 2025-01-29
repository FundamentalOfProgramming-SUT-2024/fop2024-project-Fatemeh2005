#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

extern weapon** weapons;

void food_menu(player* user){
    keypad(stdscr, TRUE);
    clear();
    
            mvprintw(0, 0,"number of your normal food units is :  %d", user ->count_food);
            mvprintw(1, 0,"number of your power food units is :  %d", user ->count_perfect_food);
            mvprintw(3, 0,"%d", user->unhungry);
            mvprintw(10, 10, "press c to consume normal food");
            mvprintw(11, 10, "press p to consume power food");
            mvprintw(12, 10, "press Q twice to exit this menu");
            mvprintw(2, 0, "how hungry you are: ");
            for(int i = 0; i<user ->unhungry; i++)
            printw(" ! ");
            char c;

            while(1){
                c  = getch();
            if(c == 'c' && user ->count_food > 0){
               user ->count_food --;
               user ->health += 4;  if(user ->health > user ->Maxhealth)    user->health = user->Maxhealth;
               user ->unhungry += 2;
               clear();
               mvprintw(0, 0,"number of your normal food units is :  %d", user ->count_food);
            mvprintw(1, 0,"number of your power food units is :  %d", user ->count_perfect_food);
            mvprintw(3, 0,"%d", user->unhungry);
            mvprintw(10, 10, "press c to consume normal food");
            mvprintw(11, 10, "press p to consume power food");
            mvprintw(12, 10, "press Q twice to exit this menu");
            mvprintw(2, 0, "how hungry you are: ");
            for(int i = 0; i<user ->unhungry; i++)
            printw(" ! ");       
    }  
    else if(c == 'p' && user ->count_perfect_food > 0){
               user ->count_food --;
               user ->health += 4;  if(user ->health > user ->Maxhealth)    user->health = user->Maxhealth;
               user ->unhungry += 2;
               clear();
               mvprintw(0, 0,"number of your normal food units is :  %d", user ->count_food);
            mvprintw(1, 0,"number of your power food units is :  %d", user ->count_perfect_food);
            mvprintw(3, 0,"%d", user->unhungry);
            mvprintw(10, 10, "press c to consume normal food");
            mvprintw(11, 10, "press p to consume power food");
            mvprintw(12, 10, "press Q twice to exit this menu");
            mvprintw(2, 0, "how hungry you are: ");
            for(int i = 0; i<user ->unhungry; i++)
            printw(" ! ");    
    }          
            else if(c == 'Q'){
                clear();
                break;
            }
    }           
}   
void weopon_menu(player* user){
    keypad(stdscr, TRUE);
    clear();
    
            mvprintw(0, 0,"number of your Mace weapon is :  %d", weapons[1]->count);
            mvprintw(1, 0,"number of your Dagger weapon is :  %d", weapons[0]->count);
            mvprintw(2, 0,"number of your Normal arrow weapon is :  %d", weapons[4]->count);
            mvprintw(3, 0,"number of your Magic wand weapon is :  %d", weapons[3]->count);
            mvprintw(4, 0,"number of your Sword weapon is :  %d", weapons[2]->count);
            mvprintw(10, 10, "press Q to exit this menu");
            mvprintw(11, 10, "press M to change your default weapon to Mace");
            mvprintw(12, 10, "press D to change your default weapon to Dagger");
            mvprintw(13, 10, "press N to change your default weapon to Normal arrow");
            mvprintw(14, 10, "press W to change your default weapon to Magic Wand");
            mvprintw(15, 10, "press S to change your default weapon to Sword");

            mvprintw(16, 10, "Your current default weapon is %c", user->default_weapon->name);
            char c;
            
            while(1){
                c  = getch();
                //add codes for changing your weopon           
             if(c == 'Q'){
                clear();
                break;
            }
            else if(c == 'M'){
                user->default_weapon = weapons[1];
            }
            else if(c == 'D' && weapons[0]->count>0){
                user->default_weapon = weapons[0];
            }
            else if(c == 'N' && weapons[4]->count>0){
                user->default_weapon = weapons[4];
            }
            else if(c == 'W' && weapons[3]->count>0){
                user->default_weapon = weapons[3];
            }
            else if(c == 'S' && weapons[2]->count>0){
                user->default_weapon = weapons[2];
            }
            mvprintw(16, 10, "Your current default weapon is %c", user->default_weapon->name);
    }           
} 
void potion_menu(player* user){
    keypad(stdscr, TRUE);
    clear();
    
            mvprintw(0, 0,"number of your Health potion is :  %d", user ->health_potion);
            mvprintw(1, 0,"number of your Speed potion is :  %d", user ->speed_potion);
            mvprintw(2, 0,"number of your Damage potion is :  %d", user ->damage_potion);
            
            mvprintw(10, 10, "press Q to exit this menu");
            mvprintw(11, 10, "press H to consume Health potion");
            mvprintw(12, 10, "press D to consume Damage potion");
            char c;
            
            while(1){
                c  = getch();
                //add codes for changing your weopon           
             if(c == 'Q'){
                clear();
                break;
            }
            else if(c == 'H'&& user ->health_potion>0){
                user->health_potion --;
                user->health = user->Maxhealth;
                mvprintw(0, 0,"number of your Health potion is :  %d", user ->health_potion);               
            }
            else if(c == 'D' && user->damage_potion>0){
                user->damage_potion --;
                user->consumed_damage_potion = 1;
            }
    }           
}
