/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** plv
*/

#include "server.h"

int plv(char **tab, t_client *client, t_info *info)
{
    t_player *player = get_player_by_id(atoi(tab[1]), info);

    if (write_into_fd(client->_fd) == 0) {
        dprintf(client->_fd, "plv %s %d\n", tab[1], player->level);
    }
    return 0;
}
