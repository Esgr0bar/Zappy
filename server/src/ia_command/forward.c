/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** forward.c
*/

#include "server.h"

void change_pos(t_info *info, int id, int change)
{
    int px = info->player[id].x;
    int py = info->player[id].y;
    int i = 0;

    for (i = 0; i < info->size_map; i++) {
        if (info->map[i]->x == px && info->map[i]->y == py) {
            info->map[i]->nb_player += change;
            break;
        }
    }
}

void forward_two(t_info *info, int id)
{
    if (info->player[id].O == BACK) {
        if (info->player[id].y == info->y)
            info->player[id].y = 0;
        else
            info->player[id].y += 1;
    }
    if (info->player[id].O == LEFT) {
        if (info->player[id].x == 0)
            info->player[id].x = info->x - 1;
        else
            info->player[id].x -= 1;
    }
}

static void share_information(t_client *c)
{
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ok\n");
    c->count_cmd = FORWARD;
    c->time_cmd = clock();
}

int forward(char **tab, t_client *c, t_info *info)
{
    int id = get_player_id(c, info);

    (void)tab;
    change_pos(info, id, -1);
    if (info->player[id].O == UP) {
        if (info->player[id].y == 0)
            info->player[id].y = info->y - 1;
        else
            info->player[id].y -= 1;
    }
    if (info->player[id].O == RIGHT) {
        if (info->player[id].x == info->x)
            info->player[id].x = 0;
        else
            info->player[id].x += 1;
    }
    forward_two(info, id);
    change_pos(info, id, 1);
    share_information(c);
    return 0;
}
