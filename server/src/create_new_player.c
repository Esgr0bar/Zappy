/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** create_new_player
*/

#include "server.h"

static void add_player_on_map(int x, int y, t_info *info)
{
    int pos_p = (x * info->x) + y;

    info->map[pos_p]->nb_player++;
}

static t_player init_player(t_client *clients, t_server *server, t_info *info)
{
    t_player player;

    player.level = 1;
    player.O = random_int(3);
    player.x = random_int(server->width - 1);
    player.y = random_int(server->height - 1);
    add_player_on_map(player.x, player.y, info);
    player.end = 0;
    player.ressource = calloc(sizeof(int), NB_RESSOURCES);
    player.ressource[FOOD] = 10;
    player.fd = clients[server->actual]._fd;
    player.id = clients[server->actual].id;
    return player;
}

int create_player(t_client *clients, t_server *server, t_info *info)
{
    if (info->player == NULL)
        info->player = calloc(sizeof(t_player), (info->nb_player + 2));
    else
        info->player = realloc(info->player,
                            sizeof(t_player) * (info->nb_player + 2));
    info->player[info->nb_player] = init_player(clients, server, info);
    info->player[info->nb_player + 1].end = 1;
    if (server->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
        dprintf(server->fd_graph, "pnw %d %d %d %d %d %s\n", info->count_id,
    info->player[info->nb_player].x, info->player[info->nb_player].y,
    info->player[info->nb_player].O, info->player[info->nb_player].level,
    clients[server->actual]._name_team);
    return 0;
}
