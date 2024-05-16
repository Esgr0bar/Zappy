/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** incantation.c
*/

#include "server.h"

int check_ressources(t_client *c, t_info *info, int id)
{
    int px = info->player[id].x;
    int py = info->player[id].y;
    int i = 0;

    (void)c;
    for (i = 0; i < info->size_map; i++) {
        if (info->map[i]->x == px && info->map[i]->y == py) {
            break;
        }
    }
    for (int j = 1; j < NB_RESSOURCES; j++) {
        if (info->map[i]->ressources[j] <
            ELEVATION[info->player[id].level - 1][j])
            return 0;
    }
    return 1;
}

int check_all(t_client *c, t_info *info, int id)
{
    int px = info->player[id].x;
    int py = info->player[id].y;
    int count = 1;

    for (int i = 0; i < info->nb_player; i++) {
        if (i != id && info->player[i].x == px &&
            info->player[i].y == py && (info->player[i].level - 1)
            == (info->player[id].level - 1)) {
            count++;
        }
    }
    if (count < ELEVATION[info->player[id].level - 1][0]) {
        return 0;
    }
    return check_ressources(c, info, id);
}

static void share_information(t_client *c, t_info *info, int id)
{
    if (write_into_fd(c->_fd) == 0) {
        dprintf(c->_fd, "Current level: %d\n", info->player[id].level);
    }
}

int elevation(t_client *c, t_info *info, int id)
{
    int px = info->player[id].x;
    int py = info->player[id].y;
    int i = 0;
    for (i = 0; i < info->size_map; i++) {
        if (info->map[i]->x == px && info->map[i]->y == py)
            break;
    }
    for (int j = 1; j < NB_RESSOURCES; j++) {
        info->map[i]->ressources[j] -=
            ELEVATION[info->player[id].level - 1][j];
    }
    for (int p = 0; p < info->nb_player; p++) {
        if (p != id && info->player[p].x == px && info->player[p].y == py
            && (info->player[p].level - 1) == (info->player[id].level - 1)) {
            info->player[p].level += 1;
        }
    }
    info->player[id].level += 1;
    share_information(c, info, id);
    return 0;
}

int incantation(char **tab, t_client *c, t_info *info)
{
    int id = get_player_id(c, info);

    (void)tab;
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "Elevation underway\n");
    if (check_all(c, info, id) == 0 && write_into_fd(c->_fd) == 0) {
        dprintf(c->_fd, "ko\n");
    } else {
        c->count_cmd = INCANTATION;
        c->time_cmd = clock();
        if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0) {
            dprintf(info->fd_graph, "pic %d %d %d %d\n", info->player[id].x,
            info->player[id].y, info->player[id].level + 1,
            info->player[id].id);
        }
    }
    return 0;
}
