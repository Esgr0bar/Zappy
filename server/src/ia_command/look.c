/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** look.c
*/

#include "server.h"

int look(char **tab, t_client *c, t_info *info)
{
    char *str = algo_look(c, info);

    (void)tab;
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "%s", str);
    free(str);
    c->count_cmd = LOOK;
    c->time_cmd = clock();
    return 0;
}
