/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** bct
*/

#include "server.h"

int bct(char **tab, t_client *client, t_info *info)
{
    int x = atoi(tab[1]);
    int y = atoi(tab[2]);
    int p = (x * info->x) + y;

    if (write_into_fd(client->_fd) == 0) {
        dprintf(client->_fd, "bct %s %s %d %d %d %d %d %d %d\n", tab[1],tab[2],
        info->map[p]->ressources[FOOD], info->map[p]->ressources[LINEMATE],
        info->map[p]->ressources[DERAUMERE], info->map[p]->ressources[SIBUR],
        info->map[p]->ressources[MENDIANE], info->map[p]->ressources[PHIRAS],
        info->map[p]->ressources[THYSTAME]);
    }
    return 0;
}
