/*
** EPITECH PROJECT, 2020
** test_totale_number.c
** File description:
** fontion
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_alphanum(char c, char *delim)
{
    if (c == '\0')
        return 2;
    for (size_t i = 0; i < strlen(delim); i++) {
        if (delim[i] == c)
            return 1;
    }
    return (0);
}

static int totale_word(char *str, char *delim)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        while (is_alphanum(str[i], delim) == 1)
            i++;
        if (str[i] == '\0')
            break;
        j++;
        while (is_alphanum(str[i], delim) == 0)
            i++;
    }
    return (j);
}

static char **alloc_memory(char *str, char **memory_word, char *delim)
{
    int i = 0;
    int h = 0;
    int count = 0;

    while (str[i] != '\0') {
        while (is_alphanum(str[i], delim) == 1)
            i++;
        if (str[i] == '\0')
            break;
        while (is_alphanum(str[i], delim) == 0) {
            i++;
            count++;
        }
        memory_word[h] = calloc(sizeof(char), count + 1);
        memory_word[h][count] = '\0';
        h++;
        count = 0;
    }
    return (memory_word);
}

static char **cpy(char *str, char **memory_word, char *delim)
{
    int i = 0;
    int h = 0;
    int g = 0;

    while (str[i] != '\0') {
        while (is_alphanum(str[i], delim) == 1)
            i++;
        if (str[i] == '\0')
            break;
        while (is_alphanum(str[i], delim) == 0) {
            memory_word[h][g] = str[i];
            i++;
            g++;
        }
        h++;
        g = 0;
    }
    return (memory_word);
}

char **my_str_to_word_array(char *str, char *delim)
{
    int word = totale_word(str, delim);
    char **memory_word = malloc(sizeof(char *) * (word + 1));

    memory_word[word] = NULL;
    alloc_memory(str, memory_word, delim);
    cpy(str, memory_word, delim);
    return (memory_word);
}
