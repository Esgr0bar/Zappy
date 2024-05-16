/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** take.c
*/

#include "server.h"

static void share_information(t_client *c, t_info *info, int i, char *elem)
{
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ok\n");
    if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
        dprintf(info->fd_graph, "pgt %d %s\n", info->player[i].id, elem);
    c->count_cmd = TAKE;
    c->time_cmd = clock();
}

void take_ressources(t_client *c, t_info *info, int res, char *elem)
{
    int id = get_player_id(c, info);
    int px = info->player[id].x;
    int py = info->player[id].y;

    for (int i = 0; i < info->size_map; i++) {
        if (info->map[i]->x == px && info->map[i]->y == py
            && info->map[i]->ressources[res] > 0) {
            info->map[i]->ressources[res] -= 1;
            info->player[id].ressource[res] += 1;
            share_information(c, info, id, elem);
            return;
        }
    }
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ko\n");
    return;
}

static int take_loop(char **tab, t_client *c, t_info *info, int i)
{
    char *res[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};

    for (int j = 0; j < NB_RESSOURCES; j++) {
        if (strcmp(tab[i], res[j]) == 0) {
            take_ressources(c, info, j, res[j]);
            return 0;
        }
    }
    return 1;
}

int take(char **tab, t_client *c, t_info *info)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (take_loop(tab, c, info, i) == 0)
            return 0;
    }
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ko\n");
    return 0;
}
