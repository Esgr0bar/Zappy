/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** broadcast.c
*/

#include "server.h"

int broadcast(char **tab, t_client *c, t_info *info)
{
    t_player *player = get_player_by_id(c->id, info);
    int result;

    for (int i = 0; info->player[i].end != 1; i++) {
        if (info->player[i].id != player->id
            && write_into_fd(info->player[i].fd) == 0) {
            result = algo_broadcast(player, &info->player[i], info);
            dprintf(info->player[i].fd, "message %d, %s\n", result, tab[1]);
        }
    }
    dprintf(c->_fd, "ok\n");
    if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
        dprintf(info->fd_graph, "pbc %d %s\n", player->id, tab[1]);
    c->count_cmd = BROADCAST;
    c->time_cmd = clock();
    return 0;
}
