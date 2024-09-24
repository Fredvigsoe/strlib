#ifndef STRLIB_H
#define STRLIB_H

#include <stddef.h> // for size_t

char str_charAt(const char *str, size_t index);
void str_concat(const char *str1, const char *str2, char *output);
int str_includes(const char *str, const char *substr);
int str_indexOf(const char *str, const char *substr);
int str_startsWith(const char *str, const char *substr);
int str_endsWith(const char *str, const char *substr);
void str_toLowerCase(char *str);
void str_toUpperCase(char *str);
int str_localeCompare(char* firstStr, char* secondStr);
void str_substring(char* str, int firstIndex, int lastIndex);
void str_trim(char *str);
void str_trimStart(char *str);
void str_trimEnd(char *str);
size_t str_length(const char *str);

#endif 
