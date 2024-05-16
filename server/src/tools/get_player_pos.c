/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** get_player_pos.c
*/

#include "server.h"

int get_player_pos(t_player *player, t_info *info)
{
    int px = player->x;
    int py = player->y;
    int i = 0;

    for (i = 0; i < info->size_map - 1; i++) {
        if (info->map[i]->x == px && info->map[i]->y == py) {
            return i;
        }
    }
    return i;
}
