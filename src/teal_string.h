#ifndef FELT_STRING_H
#define FELT_STRING_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include "teal_memory.h"

size_t
teal_str_len(char *str);

char *
teal_str_dup(char *str);

char *
teal_str_chr(char *str, char c, size_t len);

char *
teal_find_str_in_str_arr(char **arr, char *str);

bool
teal_is_substr_at_addr(char* addr, char* substr);

bool
teal_str_same(char *str, char *cmp);

char *
teal_new_str_stdin(void);

char **
teal_new_str_arr_split(char *str, char *delim);

void
teal_free_split_str(char **split_str);

#endif // FELT_STRING_H