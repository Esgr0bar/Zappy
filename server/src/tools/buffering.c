/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** buffering
*/

#include "server.h"

int *realloc_ressource(int *ressources)
{
    int *result = calloc(sizeof(int), NB_RESSOURCES);

    for (int i = 0; i != NB_RESSOURCES; i++)
        result[i] = ressources[i];
    return result;
}

char *realloc_buffer(char *buffer, char *tmp)
{
    char *stock = "";

    stock = strdup(buffer);
    free(buffer);
    buffer = malloc(sizeof(char) * (strlen(stock) + strlen(tmp)) + 1);
    buffer[strlen(stock) + strlen(tmp)] = '\0';
    strcpy(buffer, stock);
    free(stock);
    strcat(buffer, tmp);
    return buffer;
}
