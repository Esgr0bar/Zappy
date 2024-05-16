/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** get_player_id.c
*/

#include "server.h"

int get_player_id(t_client *c, t_info *info)
{
    int i = 0;

    for (i = 0; i < info->nb_player; i++) {
        if (c->id == info->player[i].id)
            return i;
    }
    return i;
}
