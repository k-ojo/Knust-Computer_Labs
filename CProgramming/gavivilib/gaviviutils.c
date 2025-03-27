
void print_header(char *str){
    printf("\t\t\033[1;35m%s\033[0m\t\t\n", str);
}

void print_options(char *str){
    printf("\033[1;33m%s\033[0m\n", str);
}

void clearConsole(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}