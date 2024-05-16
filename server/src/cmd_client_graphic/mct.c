/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** mct
*/

#include "server.h"

int mct(char **tab, t_client *client, t_info *info)
{
    (void)tab;
    for (int i = 0; i < info->size_map; i++) {
        if (write_into_fd(client->_fd) == 0) {
            dprintf(client->_fd, "bct %d %d %d %d %d %d %d %d %d\n",
            info->map[i]->x, info->map[i]->y,
            info->map[i]->ressources[FOOD], info->map[i]->ressources[LINEMATE],
            info->map[i]->ressources[DERAUMERE],info->map[i]->ressources[SIBUR],
            info->map[i]->ressources[MENDIANE],info->map[i]->ressources[PHIRAS],
            info->map[i]->ressources[THYSTAME]);
        }
    }
    return 0;
}
