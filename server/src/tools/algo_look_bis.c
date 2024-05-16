/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** algo_look_bis
*/

#include "server.h"

void check_index(int *index, t_info *info)
{
    if ((*index) < 0)
        (*index) = (*index) + info->size_map;
    if ((*index) > info->size_map - 1)
        (*index) = (*index) - info->size_map;
}
