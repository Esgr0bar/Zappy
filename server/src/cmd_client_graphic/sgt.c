/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** sgt
*/

#include "server.h"

int sgt(char **tab, t_client *client, t_info *info)
{
    (void)tab;
    if (write_into_fd(client->_fd) == 0)
        dprintf(client->_fd, "sgt %d\n", info->freq);
    return 0;
}
