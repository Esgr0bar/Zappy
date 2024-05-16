/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** init_map
*/

#include "server.h"

static int init_map(t_info *info)
{
    int size = 0;

    info->map = calloc(sizeof(t_map *), ((info->x * info->y) + 1));
    for (int i = 0; i < info->x; i++) {
        for (int j = 0; j < info->y; j++, size++) {
            info->map[size] = calloc(sizeof(t_map), 1);
            info->map[size]->ressources = calloc(sizeof(int), NB_RESSOURCES);
            info->map[size]->ressources[FOOD] = 0;
            info->map[size]->ressources[LINEMATE] = 0;
            info->map[size]->ressources[DERAUMERE] = 0;
            info->map[size]->ressources[SIBUR] = 0;
            info->map[size]->ressources[MENDIANE] = 0;
            info->map[size]->ressources[PHIRAS] = 0;
            info->map[size]->ressources[THYSTAME] = 0;
            info->map[size]->x = i;
            info->map[size]->y = j;
        }
    }
    generate_ressources(info);
    return 0;
}

int init_map_ressource(t_info *info)
{
    info->max_ressources[FOOD] = info->x * info->y * DEN_FOOD;
    info->max_ressources[LINEMATE] = info->x * info->y * DEN_LINEMATE;
    info->max_ressources[DERAUMERE] = info->x * info->y * DEN_DERAUMERE;
    info->max_ressources[SIBUR] = info->x * info->y * DEN_SIBUR;
    info->max_ressources[MENDIANE] = info->x * info->y * DEN_MENDIANE;
    info->max_ressources[PHIRAS] = info->x * info->y * DEN_PHIRAS;
    info->max_ressources[THYSTAME] = info->x * info->y * DEN_THYSTAME;
    return 0;
}

int init_team(t_info *info, t_server *server)
{
    int size = 0;

    for (; info->name_team[size] != NULL; size++);
    info->team = calloc(sizeof(t_team), size + 1);
    info->team[size].end = 1;
    for (int i = 0; info->name_team[i] != NULL; i++) {
        info->team[i].name = strdup(info->name_team[i]);
        info->team[i].nb_client = server->client_nb;
        info->team[i].id = calloc(sizeof(int), info->team[i].nb_client);
        info->team[i].end = 0;
        info->team[i].count = 0;
    }
    return 0;
}

int init_info(t_server *server, t_info *info)
{
    info->name_team = server->name_team;
    info->nb_player = 0;
    info->x = server->width;
    info->y = server->height;
    info->freq = server->freq;
    info->size_map = info->x * info->y;
    info->time_respawn = clock();
    info->max_ressources = calloc(sizeof(int), NB_RESSOURCES);
    info->player = NULL;
    info->count_id = 0;
    info->fd_graph = -1;
    init_map_ressource(info);
    init_map(info);
    init_team(info, server);
    return 0;
}
