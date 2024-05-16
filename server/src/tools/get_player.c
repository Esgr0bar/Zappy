/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** get_player
*/

#include "server.h"

t_player *get_player(t_client *client, t_info *info)
{
    for (int i = 0; info->player[i].end != 1; i++)
        if (client->id == info->player[i].id)
            return &info->player[i];
    return NULL;
}

t_player *get_player_by_id(int id, t_info *info)
{
    for (int i = 0; info->player[i].end != 1; i++)
        if (id == info->player[i].id)
            return &info->player[i];
    return NULL;
}
