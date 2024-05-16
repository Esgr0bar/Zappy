/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** parse_arg
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

static int get_size(char **argv, int index)
{
    int size = 0;

    for (; argv[index] != NULL; index++, size++) {
        if (strcmp(argv[index], "-p") == 0)
            break;
        if (strcmp(argv[index], "-x") == 0)
            break;
        if (strcmp(argv[index], "-y") == 0)
            break;
        if (strcmp(argv[index], "-c") == 0)
            break;
        if (strcmp(argv[index], "-f") == 0)
            break;
    }
    return size;
}

static int fill_struct(int *index, char **argv, t_args *args)
{
    int old_index = *(index);
    int size = get_size(argv, old_index + 1);

    if (size == 0) {
        (*index) -= 2;
        return -1;
    }
    (*index) += 1;
    args->name_team = malloc(sizeof(char *) * (size + 1));
    args->name_team[size] = NULL;
    for (int i = 0; i != size; i++, (*index)++)
        args->name_team[i] = strdup(argv[(*index)]);
    (*index) -= 2;
    return 0;
}

static int check_args(t_args *args)
{
    if (args->port == 0)
        return -1;
    if (args->width == 0)
        return -1;
    if (args->height == 0)
        return -1;
    if (args->freq == 0)
        return -1;
    if (args->clientNb == 0)
        return -1;
    if (args->name_team == NULL)
        return -1;
    return 0;
}

void init_struct(t_args *args)
{
    args->clientNb = 0;
    args->freq = 0;
    args->height = 0;
    args->name_team = NULL;
    args->port = 0;
    args->width = 0;
}

int parse_args(t_args *args, char **argv)
{
    init_struct(args);
    for (int i = 1; argv[i] != NULL; i = i + 2) {
        if (strcmp(argv[i], "-p") == 0 && argv[i + 1] != NULL)
            args->port = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-x") == 0 && argv[i + 1] != NULL)
            args->width = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-y") == 0 && argv[i + 1] != NULL)
            args->height = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-n") == 0 && argv[i + 1] != NULL
            && fill_struct(&i, argv, args) != -1)
            continue;
        if (strcmp(argv[i], "-c") == 0 && argv[i + 1] != NULL)
            args->clientNb = atoi(argv[i + 1]);
        if (strcmp(argv[i], "-f") == 0 && argv[i + 1] != NULL)
            args->freq = atoi(argv[i + 1]);
    }
    return check_args(args);
}
