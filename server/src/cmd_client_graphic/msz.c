/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** mzt
*/

#include "server.h"

int msz(char **tab, t_client *client, t_info *info)
{
    (void)tab;
    if (write_into_fd(client->_fd) == 0) {
        dprintf(client->_fd, "msz %d %d\n", info->x, info->y);
    }
    return 0;
}
