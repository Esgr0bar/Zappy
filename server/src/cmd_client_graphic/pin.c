/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** pin
*/

#include "server.h"

int pin(char **tab, t_client *client, t_info *info)
{
    t_player *player = get_player_by_id(atoi(tab[1]), info);

    if (write_into_fd(client->_fd) == 0) {
        dprintf(client->_fd, "pin %s %d %d %d %d %d %d %d %d %d\n",
        tab[1], player->x, player->y,
        player->ressource[FOOD], player->ressource[LINEMATE],
        player->ressource[DERAUMERE], player->ressource[SIBUR],
        player->ressource[MENDIANE], player->ressource[PHIRAS],
        player->ressource[THYSTAME]);
    }
    return 0;
}
