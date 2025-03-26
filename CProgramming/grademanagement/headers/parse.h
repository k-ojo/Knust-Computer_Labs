#ifndef _PARSE
#define _PARSE

#include "main.h"

char *parse_attribute(char *buf, user *u, attr att, char delim);
user *parse_user(char *buf, char delim);

#endif