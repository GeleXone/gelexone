#pragma once
#include "Xone/xone.h"

//Количество СИМВОЛОВ, без '\0'
unsigned int x_strlen(const char* string);
char* x_strcat(char* base_string, const char* other_string);
char* x_straddc(char* base, char c);
boolean x_strcmp(char* a, char* b);
boolean x_is_substring(const char* sub, char* origin);
