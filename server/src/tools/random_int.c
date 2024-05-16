/*
** EPITECH PROJECT, 2023
** server
** File description:
** random_pos_player
*/

#include "server.h"

int random_int(int limit)
{
    srand(time(NULL));

    return (rand() % (limit));
}
