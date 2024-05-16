/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** eject.c
*/

#include "server.h"

void eject_player(t_info *info, int id)
{
    if (info->player[id].O == UP)
        info->player[id].y -= 1;
    if (info->player[id].O == RIGHT)
        info->player[id].x += 1;
    if (info->player[id].O == BACK)
        info->player[id].y += 1;
    if (info->player[id].O == LEFT)
        info->player[id].x -= 1;
}

static void share_information(t_client *c, t_info *info, int count, int id)
{
    if (count != 0 && write_into_fd(c->_fd) == 0) {
        c->count_cmd = EJECT;
        c->time_cmd = clock();
        dprintf(c->_fd, "ok\n");
    } else if (count == 0 && write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ko\n");
    if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
        dprintf(info->fd_graph, "pex %d\n", info->player[id].id);
}

int eject(char **tab, t_client *c, t_info *info)
{
    int id = get_player_id(c, info);
    int px = info->player[id].x;
    int py = info->player[id].y;
    int count = 0;

    (void)tab;
    for (int i = 0; i < info->nb_player; i++) {
        if (i != id && info->player[i].x == px && info->player[i].y == py) {
            eject_player(info, i);
            count++;
        }
    }
    share_information(c, info, count, id);
    return 0;
}
