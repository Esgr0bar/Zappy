/*
** EPITECH PROJECT, 2023
** server
** File description:
** algo_look
*/

#include "server.h"

char *algo_look_up(t_player *player, t_info *info)
{
    int pos_p = get_player_pos(player, info);
    int repeat = 3;
    int decrement = -1;
    int index = 0;
    char *buffer = calloc(sizeof(char), 1);

    buffer = realloc_buffer(buffer, "[");
    buffer = print_tile(buffer, info->map[pos_p]);
    for (int i = 0; i != player->level; i++,
        decrement = decrement - 1, repeat = repeat + 2) {
        for (int j = 0, tmp = decrement; j != repeat; j++, tmp++) {
            index = pos_p - (info->x * (i + 1)) + tmp;
            check_index(&index, info);
            buffer = print_tile(buffer, info->map[index]);
        }
    }
    buffer[strlen(buffer) - 1] = '\0';
    buffer = realloc_buffer(buffer, "]\n");
    return buffer;
}

char *algo_look_right(t_player *player, t_info *info)
{
    int pos_p = get_player_pos(player, info);
    int repeat = 3;
    int tmp = 1;
    int index = 0;
    char *buffer = calloc(sizeof(char), 1);

    buffer = realloc_buffer(buffer, "[");
    buffer = print_tile(buffer, info->map[pos_p]);
    for (int i = 0; i != player->level; i++, repeat = repeat + 2, tmp++) {
        for (int j = 0; j != repeat; j++) {
            index = pos_p - (info->x * (i + 1)) + (info->y * j) + tmp;
            check_index(&index, info);
            buffer = print_tile(buffer, info->map[index]);
        }
    }
    buffer[strlen(buffer) - 1] = '\0';
    buffer = realloc_buffer(buffer, "]\n");
    return buffer;
}

char *algo_look_back(t_player *player, t_info *info)
{
    int pos_p = get_player_pos(player, info);
    int repeat = 3;
    int decrement = 1;
    int index = 0;
    char *buffer = calloc(sizeof(char), 1);

    buffer = realloc_buffer(buffer, "[");
    buffer = print_tile(buffer, info->map[pos_p]);
    for (int i = 0; i != player->level;
    i++, decrement = decrement + 1, repeat = repeat + 2) {
        for (int j = 0, tmp = decrement; j != repeat; j++, tmp--) {
            index = pos_p + (info->x * (i + 1)) + tmp;
            check_index(&index, info);
            buffer = print_tile(buffer, info->map[index]);
        }
    }
    buffer[strlen(buffer) - 1] = '\0';
    buffer = realloc_buffer(buffer, "]\n");
    return buffer;
}

char *algo_look_left(t_player *player, t_info *info)
{
    int pos_p = get_player_pos(player, info);
    int repeat = 3;
    int tmp = -1;
    int index = 0;
    char *buffer = calloc(sizeof(char), 1);

    buffer = realloc_buffer(buffer, "[");
    buffer = print_tile(buffer, info->map[pos_p]);
    for (int i = 0; i != player->level; i++, repeat = repeat + 2, tmp--) {
        for (int j = 0; j != repeat; j++) {
            index = pos_p + (info->x * (i + 1)) - (info->y * j) + tmp;
            check_index(&index, info);
            buffer = print_tile(buffer, info->map[index]);
        }
    }
    buffer[strlen(buffer) - 1] = '\0';
    buffer = realloc_buffer(buffer, "]\n");
    return buffer;
}

char *algo_look(t_client *client, t_info *info)
{
    t_player *player = get_player(client, info);

    if (player->O == UP)
        return algo_look_up(player, info);
    if (player->O == RIGHT)
        return algo_look_right(player, info);
    if (player->O == BACK)
        return algo_look_back(player, info);
    if (player->O == LEFT)
        return algo_look_left(player, info);
    return NULL;
}
