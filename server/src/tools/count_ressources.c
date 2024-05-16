/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** count_ressources.c
*/

#include "server.h"

int count_ressources(t_info *info, int ressource)
{
    int count = 0;

    for (int i = 0; i < info->size_map; i++) {
        count += info->map[i]->ressources[ressource];
    }
    return count;
}
