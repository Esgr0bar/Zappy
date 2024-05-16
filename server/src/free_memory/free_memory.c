/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** free_memory
*/

#include "server.h"

void free_player(t_player *player)
{
    if (player != NULL) {
        for (int i = 0; player[i].end != 1; i++)
            free(player[i].ressource);
        free(player);
    }
}

void free_team(t_team *team)
{
    for (int i = 0; team[i].end != 1; i++) {
        free(team[i].name);
        free(team[i].id);
    }
    free(team);
}

void free_array(char **tmp)
{
    for (int i = 0; tmp[i] != NULL; i++)
        free(tmp[i]);
    free(tmp);
}

void free_all(t_server *server, t_info *info)
{
    free(server);
    free_array(info->name_team);
    for (int i = 0; i < info->size_map; i++) {
        free(info->map[i]->ressources);
        free(info->map[i]);
    }
    free(info->map);
    free(info->max_ressources);
    free_player(info->player);
    free_team(info->team);
    free(info);
}
