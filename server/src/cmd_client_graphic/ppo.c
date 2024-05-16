/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ppo
*/

#include "server.h"

int ppo(char **tab, t_client *client, t_info *info)
{
    t_player *player = get_player_by_id(atoi(tab[1]), info);

    if (write_into_fd(client->_fd) == 0) {
        dprintf(client->_fd, "ppo %d %d %d %d\n",
            player->id, player->x, player->y, player->O);
    }
    return 0;
}
