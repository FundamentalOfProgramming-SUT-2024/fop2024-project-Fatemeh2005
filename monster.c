#include <ncurses.h>
#include <stdlib.h>
#include "map.h"
extern char** map;
extern int level;
extern int ** visited;
extern monster** monsters;

int moveMonsters(user, monsters){
    int x;
    for(x=0; x<3; x++){
        pathfindingseek(monsters[x]->position, user);
    }

}