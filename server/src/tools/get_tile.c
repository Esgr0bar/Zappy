/*
** EPITECH PROJECT, 2023
** server
** File description:
** print_tile
*/

#include "server.h"

char *print_tile(char *buffer, t_map *map)
{
    char *tmp[7] = {"food ", "linemate ", "deraumere ", "sibur ",
        "mendiane ", "phiras ", "thystame "};
    char *tmp_bis[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};

    for (int i = 0; i != map->nb_player; i++) {
        if (i > 0 && (i + 1) < map->nb_player)
            buffer = realloc_buffer(buffer, " ");
        buffer = realloc_buffer(buffer, "player ");
    }
    for (int i = 0; i != NB_RESSOURCES; i++) {
        if (i > 0 && (i + 1) < NB_RESSOURCES && map->ressources[i] != 0)
            buffer = realloc_buffer(buffer, " ");
        for (int j = 0; j != map->ressources[i]; j++)
            buffer = realloc_buffer(buffer, tmp[i]);
        if (map->ressources[i] != 0)
            buffer = realloc_buffer(buffer, tmp_bis[i]);
    }
    buffer = realloc_buffer(buffer, ",");
    return buffer;
}
