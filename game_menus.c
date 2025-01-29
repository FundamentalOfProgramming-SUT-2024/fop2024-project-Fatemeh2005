#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

void food_menu(player* user){
    keypad(stdscr, TRUE);
    clear();
    
            mvprintw(0, 0,"number of your food units is :  %d", user ->count_food);
            
            mvprintw(10, 10, "press c to consume food");
            mvprintw(11, 10, "press Q twice to exit this menu");
            mvprintw(1, 0, "how hungry you are: ");
            for(int i = 0; i<user ->unhungry; i++)
            printw(" ! ");
            char c;

            while(1){
                c  = getch();
            if(c == 'c' && user ->count_food > 0){
               user ->count_food --;
               user ->health += 4;
               user ->unhungry += 2;
               clear();
               mvprintw(0, 0,"number of your food units is :  %d", user ->count_food);
               mvprintw(10, 10, "press c to consume food");
               mvprintw(11, 10, "press Q to exit this menu");
               mvprintw(1, 0, "how hungry you are: ");
            for(int i = 0; i<10 - user ->unhungry; i++){
            printw(" ! ");
            }    
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
    
            mvprintw(0, 0,"number of your Mace weopon is :  %d", user ->Mweapon);
            mvprintw(1, 0,"number of your Dagger weopon is :  %d", user ->Dweapon);
            mvprintw(2, 0,"number of your Normal arrow weopon is :  %d", user ->Nweapon);
            mvprintw(3, 0,"number of your Magic wand weopon is :  %d", user ->Wweapon);
            mvprintw(4, 0,"number of your Sword weopon is :  %d", user ->Sweapon);
            mvprintw(10, 10, "press Q to exit this menu");
            char c;
            
            while(1){
                c  = getch();
                //add codes for changing your weopon           
             if(c == 'Q'){
                clear();
                break;
            }
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
    }           
}
