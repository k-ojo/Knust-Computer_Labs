#include "main.h"

const char delim = '|';

int save(const char *path, const char delim, student_o *s){
    FILE *f = fopen(path, "a");
    int l = fprintf(f, "%s%c%s%c%s%c%s%c%s\n", s->reference, delim, s->index, delim, s->sex, delim, s->name, delim, s->email);
    fclose(f);
    return (l);
}

void cpystr(char **s, char *str){
    *s = (char *)malloc(sizeof(char) * strlen(str));
    memcpy(*s, str, strlen(str));
}

student_o *init_student(char *name, char *email, char *ref, char *index, char *sex){
    student_o *s = (student_o *)malloc(sizeof(student_o));
    cpystr(&s->name, name);
    cpystr(&s->email, email);
    cpystr(&s->reference, ref);
    cpystr(&s->index, index);
    cpystr(&s->sex,sex);
    return s;
}

void free_student(student_o *s){
    free(s->email);
    free(s->name);
    free(s->reference);
    free(s->sex);
    free(s->index);
    free(s);
}

char *lookup(char *ref, const char* path){
    char *buf = NULL;
    size_t len = 4;
    int n = strlen(ref);

    FILE *f = fopen(path, "r");
    if (f == NULL){
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    

    while(getline(&buf, &len, f) != -1){
        if (strncmp(ref, buf, n) == 0){
            fclose(f);
            return(buf);
        }
    }
    free(buf);
    fclose(f);
    return NULL;
}

student_o *getStudent(char *ref, const char* path){
    char buf[MAX_C], *line = lookup(ref, path);
    student_o *s;

    if (!line)
        return NULL;
    s = (student_o *)malloc(sizeof(student_o));


    if (!s)
        perror("Failed to allocate student");
     return NULL;
}

int main(){
    student_o *s = init_student("Gideon", "gavivi@ga.com", "9128198098", "91092871928", "male");
    //save("student.db", delim, s);

    char *str = lookup("9128198098", "student.db");
    printf("%s", str);

    free(str);
    free_student(s);
    return (0);
}