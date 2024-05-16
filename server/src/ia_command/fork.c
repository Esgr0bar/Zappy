/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** fork.c
*/

#include "server.h"

int find_team_id(t_info *info, char *name)
{
    int i = 0;

    for (i = 0; info->team[i].end != 1; i++) {
        if (strcmp(name, info->team[i].name) == 0)
            return i;
    }
    return i;
}

int fork_ia(char **tab, t_client *c, t_info *info)
{
    int id = get_player_id(c, info);
    int team_id = find_team_id(info, c->_name_team);

    (void)tab;
    info->team[team_id].nb_client += 1;
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "ok\n");
    if (info->fd_graph != -1 && write_into_fd(info->fd_graph) == 0) {
        dprintf(info->fd_graph, "pfk %d\n", info->player[id].id);
    }
    c->count_cmd = FORK;
    c->time_cmd = clock();
    return 0;
}
