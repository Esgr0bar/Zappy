/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** sst
*/

#include "server.h"

int sst(char **tab, t_client *client, t_info *info)
{
    info->freq = atoi(tab[1]);
    if (write_into_fd(client->_fd) == 0)
        dprintf(client->_fd, "sst %d\n", info->freq);
    return 0;
}
