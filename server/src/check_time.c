/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** check_time
*/

#include "server.h"

static int check_cmd(t_client *client, t_info *info)
{
    int i = get_player_id(client, info);

    if (client->count_cmd == INCANTATION) {
        elevation(client, info, i);
        if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
            dprintf(info->fd_graph, "pie %d %d %d\n", info->player[i].x,
            info->player[i].y, info->player[i].level);
    }
    if (client->count_cmd == FORK) {
        if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
            dprintf(info->fd_graph, "enw 0 %d %d %d\n", info->player[i].id,
            info->player[i].x, info->player[i].y);
    }
    return 0;
}

static int check_food(t_client client, t_info *info)
{
    t_player *player = get_player_by_id(client.id, info);

    player->ressource[FOOD]--;
    return 0;
}

int update_time(t_info *info, t_client *clients, t_server *server)
{
    if (((double)(clock() - info->time_respawn) / CLOCKS_PER_SEC)
        >= RESPAWN_RESSOURCES_UNIT / info->freq) {
        info->time_respawn = clock();
        generate_ressources(info);
    }
    for (int i = 0; i < server->actual; i++) {
        if (clients[i].mode == GRAPHIQUE)
            continue;
        if (((double)(clock() - clients[i].time_life) / CLOCKS_PER_SEC)
            >= TIME_LIFE / info->freq) {
            check_food(clients[i], info);
            clients[i].time_life = clock();
        }
        if (((double)(clock() - clients[i].time_cmd) / CLOCKS_PER_SEC)
            >= clients[i].count_cmd / info->freq) {
            check_cmd(&clients[i], info);
            clients[i].count_cmd = 0;
        }
    }
    return 0;
}
