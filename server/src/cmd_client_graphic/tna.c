/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tna
*/

#include "server.h"

int tna(char **tab, t_client *client, t_info *info)
{
    (void)tab;
    for (int i = 0; info->name_team[i] != NULL; i++) {
        if (write_into_fd(client->_fd) == 0)
            dprintf(client->_fd, "tna %s\n", info->name_team[i]);
    }
    return 0;
}
