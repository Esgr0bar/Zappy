/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** connect_nbr.c
*/

#include "server.h"

int connect_nbr(char **tab, t_client *c, t_info *info)
{
    int index = 0;

    (void)tab;
    for (; info->team[index].end != 1; index++)
        if (strcmp(info->team[index].name, c->_name_team) == 0)
            break;
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "%d\n", info->team[index].nb_client);
    return 0;
}
