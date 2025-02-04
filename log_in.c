#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include"pregame_menu.c"
#include <ctype.h>

#define FILE_NAME "users.txt"
#define SCOREBOARD_FILE "scoreboard.txt"

void trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) // All spaces
        return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null-terminate the string
    *(end + 1) = 0;
}

int login(const char *username, const char *password, const char *email) {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return 0; // File not found
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        // Parse the line
        char *stored_username = strtok(line, ",");
        char *stored_password = strtok(NULL, ",");
        char *stored_email = strtok(NULL, ",");
        
        // Trim any extra spaces from the parsed values
        if (stored_username) trim_whitespace(stored_username);
        if (stored_password) trim_whitespace(stored_password);
        if (stored_email) trim_whitespace(stored_email);
        
        if (stored_password) {
            char *newline = strchr(stored_password, '\n');
            if (newline) *newline = '\0';  // Remove newline if present
        }

        if (stored_username && stored_password && stored_email) {
            // Compare username first
            if (strcmp(stored_username, username) == 0) {
                // If the password is provided, check if it matches
                if (password && strcmp(stored_password, password) == 0) {
                    fclose(file);
                    return 1; // Successful login
                }
                // If email is provided (for password retrieval), check if it matches
                if (email && strcmp(stored_email, email) == 0) {
                    // Forgot Username case: print password
                    printw("Your password is: %s\n", stored_password);
                    getch();
                    fclose(file);
                    return 2; // Password retrieval successful
                }
            }
        }
    }
    fclose(file);
    return 0; // Invalid username or no matching account
}
int log_in(player* user) {
    initscr();
    clear();
    keypad(stdscr, TRUE);

    int height = 13, width = 50, start_y = 8, start_x = 15;
    WINDOW *win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);

    char name[20] = "";
    char password[30] = "";
    char email[30] = "";

    mvwprintw(win, 1, 1, "Username: ");
    mvwprintw(win, 2, 1, "Password: ");
    mvwprintw(win, 3, 1, "Forgot Username? (Y/N): ");
    wrefresh(win);

    wmove(win, 1, 11);
    wgetnstr(win, name, 19);
    trim_whitespace(name); // Trim the username input

    wmove(win, 2, 11);
    wgetnstr(win, password, 29);
    trim_whitespace(password); // Trim the password input

    char forgot_username_choice;
    wmove(win, 3, 21);
    wgetnstr(win, &forgot_username_choice, 1);

    if (forgot_username_choice == 'Y' || forgot_username_choice == 'y') {
        mvwprintw(win, 4, 1, "Enter your Email: ");
        wrefresh(win);

        wmove(win, 5, 1);
        wgetnstr(win, email, 29);
        trim_whitespace(email); // Trim the email input

        if (login(name, NULL, email) == 2) {
            printw("Password retrieval successful.\n");
            getch();
        } else {
            printw("No matching account found for the provided username and email.\n");
        }
    } else {
        if (login(name, password, NULL)) {
            printw("Login successful!");
            getch();
            for (int i = 0; i < 30; i++) {
                user->username[i] = name[i];
            }
            return 1;
        } else {
            printw("Error: Invalid Username or Password!");
        }
    }

    wrefresh(win);
    getch();
    delwin(win);
    endwin();

    return 0;
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
    mvwprintw(win, 4, 1, "Use a random password? (y/n): ");
    wrefresh(win);

    wmove(win, 1, 11);
    wgetnstr(win, name, 19);

    wmove(win, 2, 11);
    wgetnstr(win, password, 29);

    wmove(win, 3, 11);
    wgetnstr(win, email, 19);

    char use_random_password = 'n';
    wmove(win, 4, 22);
    use_random_password = wgetch(win);  // Get 'y' or 'n' for random password

    if (use_random_password == 'y' || use_random_password == 'Y') {
        // Generate a random password
        generate_random_password(password, 12);  // 12 character random password

        // Display the generated password for the user to note down
        mvwprintw(win, 5, 1, "Your randomly generated password: %s", password);
        wrefresh(win);
        getch();  // Wait for user to acknowledge the displayed password
    }

    if (username_exists(name)) {
        printw("Error: Username already exists!");
        getch();
        clear();
        return 0;
    }
    else if (!pass_validation(password)) {
        printw("Error: Password is not acceptable!");
        getch();
        clear();
        return 0;
    }
    else if (!email_validation(email)) {
        printw("Error: Email not acceptable!");
        getch();
        clear();
        return 0;
    }
    else {
        save_user(name, password, email);
        save_to_scoreboard(name);

        // Optionally, print the generated password if it was generated randomly
        if (use_random_password == 'y' || use_random_password == 'Y') {
            mvprintw(0, 0, "Password saved: %s", password);
            refresh();
        }

        for (int i = 0; i < 30; i++) {
            user->username[i] = name[i];
        }
        getch();
        clear();
        return 1;
    }

    wrefresh(win);
    getch();

    delwin(win);
    endwin();
}

void generate_random_password(char *password, int length) {
    const char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lower[] = "abcdefghijklmnopqrstuvwxyz";
    const char digits[] = "0123456789";
    const char all_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    srand(time(NULL));  // Seed the random number generator

    int has_upper = 0, has_lower = 0, has_digit = 0;

    // Ensure at least one uppercase, one lowercase, and one digit
    while (!has_upper || !has_lower || !has_digit) {
        for (int i = 0; i < length - 1; i++) {
            int index = rand() % (sizeof(all_chars) - 1);  // Randomly pick a character
            password[i] = all_chars[index];
            
            if (password[i] >= 'A' && password[i] <= 'Z') has_upper = 1;
            if (password[i] >= 'a' && password[i] <= 'z') has_lower = 1;
            if (password[i] >= '0' && password[i] <= '9') has_digit = 1;
        }
        password[length - 1] = '\0';  // Null-terminate the string
    }
}
void save_to_scoreboard(const char *username) {
    FILE *file = fopen(SCOREBOARD_FILE, "a"); 
    if (file != NULL) {
        fprintf(file, "%s, %d, %d, %d\n", username, 0, 0, 0);
        fclose(file);
    }
}