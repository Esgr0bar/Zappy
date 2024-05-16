/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** right.c
*/

#include "server.h"

int right_ia(char **tab, t_client *c, t_info *info)
{
    int id = get_player_id(c, info);

    (void)tab;
    if (info->player[id].O == UP)
        info->player[id].O = RIGHT;
    if (info->player[id].O == RIGHT)
        info->player[id].O = BACK;
    if (info->player[id].O == BACK)
        info->player[id].O = LEFT;
    if (info->player[id].O == LEFT)
        info->player[id].O = UP;
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ok\n");
    c->count_cmd = RIGHT_CMD;
    c->time_cmd = clock();
    return 0;
}
