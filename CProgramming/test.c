#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <limits.h>
#include <sqlite3.h>


#ifdef _WIN32
#include <conio.h>
#define GETCH getch()
#else

#include <termios.h>
#include <unistd.h>
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

#define GETCH getch()
#endif

#define MAX_USERS 100

typedef struct {
    int id;
    char name[50];
    char email[50];
    int hashed_pin;  // Store hashed password in real applications
} User;

int getpin(){
    char pin_str[100];  
    int i = 0;
    char ch;

    printf("Enter PIN: ");

    while (1) {
        ch = GETCH;  // Platform-independent single keypress

        if (ch == '\n' || ch == '\r') {  // Enter key
            printf("*\n");  // Erase last '*'
            break;
        }

        if (isdigit(ch)) {  // Only accept numbers
            pin_str[i++] = ch;
            printf("*");  // Mask input
        } else if ((ch == '\b' || ch == 127) && i > 0) {  // Handle backspace
            i--;
            printf("\b \b");  // Erase last '*'
        }
    }

    pin_str[i] = '\0';  // Null-terminate
    int pin = atoi(pin_str);
    return pin;
}

void register_user(User *u) {
    sqlite3 *db;
    char *err_msg = 0;

    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (name, email, password) VALUES ('%s', '%s', '%d');", u->name, u->email, u->hashed_pin);

    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        printf("Error inserting user: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("User registered successfully!\n");
    }

    sqlite3_close(db);
}

#include <stdio.h>
#include <sqlite3.h>

int authenticate_user(const char *email, int password) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int stored_password = -1;  // Default invalid value

    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    const char *sql = "SELECT password FROM users WHERE email = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            stored_password = sqlite3_column_int(stmt, 0);  // Get password as int
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return (stored_password == password);  // Return 1 if match, 0 if not
}


int main(){
    User user;
    //scanf("%i %s %s %d", &user.id, user.name, user.email, &user.hashed_pin);
    //register_user(&user);
    if (authenticate_user("gideonad@gmail.com", 1441))
        printf("Access\n");
    else
        printf("Access denied\n");
}
