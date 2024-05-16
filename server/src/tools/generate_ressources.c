/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** generate_ressources.c
*/

#include "server.h"

static void fill_ressources(t_info *info, int ressource)
{
    int pos = 0;

    srand(time(NULL));
    for (int i = count_ressources(info, ressource);
        i < info->max_ressources[ressource]; i++) {
        pos = rand() % (info->size_map);
        info->map[pos]->ressources[ressource]++;
    }
}

void generate_ressources(t_info *info)
{
    for (int i = 0; i < NB_RESSOURCES; i++) {
        fill_ressources(info, i);
    }
}
