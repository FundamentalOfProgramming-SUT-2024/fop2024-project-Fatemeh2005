#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"pregame_menu.c"

#define FILE_NAME "users.txt"
#define SCOREBOARD_FILE "scoreboard.txt"

int login(const char *username, const char *password) {
    FILE *file = fopen(FILE_NAME, "r"); 
    if (file == NULL) {
        return 0; 
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *stored_username = strtok(line, ",");
        char *stored_password = strtok(NULL, ",");
        
        if (stored_password) {
            char *newline = strchr(stored_password, '\n');
            if (newline) *newline = '\0';
        }
        if (stored_username && stored_password &&
            strcmp(stored_username, username) == 0 &&
            strcmp(stored_password, password) == 0) {
            fclose(file);
            return 1; 
        }
    }
    fclose(file);
    return 0; 
}
int log_in(player* user) {
    //initscr();  
   // cbreak(); 
   clear();  
    keypad(stdscr, TRUE); 

    int height = 13, width = 50, start_y = 8, start_x = 15;
    WINDOW *win = newwin(height, width, start_y, start_x); 
    box(win, 0, 0); 

    char name[20] = "";     
    char password[30] = ""; 

    mvwprintw(win, 1, 1, "Username: ");  
    mvwprintw(win, 2, 1, "Password: ");
    wrefresh(win); 

    wmove(win, 1, 11);  
    wgetnstr(win, name, 19); 

    wmove(win, 2, 11);  
    wgetnstr(win, password, 29);  

    if (login(name, password)) {
        printw( "Login successful!"); 
        for(int i =0; i<30; i++){
            user->username[i] = name[i];
        }
       int k = pregame(user);
        getch();
        clear(); 
        return  k;
    } else {
        printw("Error: Invalid Username or Password!");  
        wrefresh(win);
        getch(); 
        return 0;
    }
    wrefresh(win); 
    getch();  

    delwin(win);  
    endwin();  
}
///////////////////////////////////////////////////////////////////////////////////////used to be sig in file
void save_user(const char *username, const char *password, const char *email) {
    FILE *file = fopen(FILE_NAME, "a"); 
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s,%s,%s\n", username, password, email); 
    fclose(file);
}

int username_exists(const char *username) {
    FILE *file = fopen(FILE_NAME, "r"); 

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char *stored_username = strtok(line, ",");  
        if (stored_username != NULL && strcmp(stored_username, username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0; 
}

int pass_validation(char password[30]) {
    int len = 0;
    while (password[len] != '\n' && password[len] != '\0') {
        len++;
    }

    if (len < 7) {
        return 0;
    }

    int check = 0;
    for (int i = 0; i < len; i++) {
        if (password[i] <= '9' && password[i] >= '0') {
            check++;
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        if (password[i] <= 'Z' && password[i] >= 'A') {
            check++;
            break;
        }
    }

    for (int i = 0; i < len; i++) {
        if (password[i] <= 'z' && password[i] >= 'a') {
            check++;
            break;
        }
    }
    return check == 3; 
}

int email_validation(char email[20]) {
    int len = 0;
    while (email[len] != '\n' && email[len] != '\0') {
        len++;
    } 
    int last_dot = len;     
    for (int i = len; i > 0; i--) {
        if (email[i] == '.') {
            last_dot = i;
            break;
        }
    }
    if (last_dot == len) { return 0; }
    int last_addsign = last_dot;
    for (int i = last_dot; i > 0; i--) {
        if (email[i] == '@') {
            last_addsign = i;
            break;
        }
    }
    if (last_addsign == last_dot || last_addsign == last_dot - 1) {
        return 0;
    }
    return 1; 
}

int sign_in(player* user) {
    initscr();  
    cbreak();  
    keypad(stdscr, TRUE); 

    int height = 13, width = 50, start_y = 8, start_x = 15;
    WINDOW *win = newwin(height, width, start_y, start_x); 
    box(win, 0, 0); 

    char name[20] = "";     
    char password[30] = ""; 
    char email[20] = "";

    mvwprintw(win, 1, 1, "Username: ");  
    mvwprintw(win, 2, 1, "Password: ");  
    mvwprintw(win, 3, 1, "Email: ");
    wrefresh(win); 

    wmove(win, 1, 11);  
    wgetnstr(win, name, 19); 

    wmove(win, 2, 11);  
    wgetnstr(win, password, 29);  

    wmove(win, 3, 11);
    wgetnstr(win, email, 19);  

    if (username_exists(name)) {
        printw( "Error: Username already exists!");  
        getch(); 
        clear();
        return 0;
    } 
    else if (!pass_validation(password)) {
        printw( "Error: Password is not acceptable!");   
        getch();
        clear();
        return 0;  
    }
    else if (!email_validation(email)) {
        printw( "Error: Email not acceptable!"); 
        getch();  
        clear();
        return 0;
    }
    else {
        save_user(name, password, email);   
       // printw( "User registered successfully!"); 
       save_to_scoreboard(name); 
       for(int i =0; i<30; i++){
            user->username[i] = name[i];
        } 
       int k = pregame(user);
        getch();
        clear(); 
        return  k;
    }

     wrefresh(win); 
    getch();  

    delwin(win);  
    endwin(); 
}
void save_to_scoreboard(const char *username) {
    FILE *file = fopen(SCOREBOARD_FILE, "a"); 
    if (file != NULL) {
        fprintf(file, "%s, %d, %d, %d\n", username, 0, 0, 0);
        fclose(file);
    }
}