/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** delete_client
*/

#include "server.h"

static void remove_player(t_client *client, t_info *info)
{
    t_player *players = calloc(sizeof(t_player), info->nb_player);

    for (int i = 0, j = 0; info->player[i].end != 1; i++) {
        if (info->player[i].id != client->id) {
            players[j].end = 0;
            players[j].fd = info->player[i].fd;
            players[j].id = info->player[i].id;
            players[j].level = info->player[i].level;
            players[j].O = info->player[i].O;
            players[j].ressource = realloc_ressource(info->player[i].ressource);
            players[j].x = info->player[i].x;
            players[j++].y = info->player[i].y;
        }
    }
    if (write_into_fd(client->_fd) == 0)
        dprintf(client->_fd, "dead\n");
    free_player(info->player);
    info->player = players;
    info->nb_player--;
    info->player[info->nb_player].end = 1;
}

static void remove_team(t_client *client, t_info *info, t_server *server)
{
    int index = 0;
    int *array = calloc(sizeof(int), server->client_nb);

    for (; info->team[index].end != 1; index++) {
        if (strcmp(info->team[index].name, client->_name_team) == 0)
            break;
    }
    for (int i = 0, j = 0; j != server->client_nb; j++) {
        if (info->team[index].id[j] != client->id) {
            array[i] = info->team[index].id[j];
            i++;
        }
    }
    free(info->team[index].id);
    info->team[index].id = array;
    info->team[index].count--;
    info->team[index].nb_client++;

}

void remove_client(t_client *clients, int index, t_server *server, t_info *info)
{
    if (clients[index].mode != GRAPHIQUE) {
        remove_player(&clients[index], info);
        remove_team(&clients[index], info, server);
    } else {
        info->fd_graph = -1;
        server->fd_graph = -1;
    }
    if (server->fd_graph != -1 && write_into_fd(info->fd_graph) == 0)
        dprintf(server->fd_graph, "pdi %d\n", clients[index].id);
    close(clients[index]._fd);
    if (clients[index]._name_team != NULL)
        free(clients[index]._name_team);
    if (clients[index]._buffer != NULL)
        free(clients[index]._buffer);
    memmove(clients + index, clients + index + 1,
    (server->actual - index - 1) * sizeof(t_client));
    server->actual--;
}

void delete_all_client(t_client *clients, t_server *server, t_info *info)
{
    while (server->actual != 0)
        remove_client(clients, 0, server, info);
}

void delete_client(t_client *clients, t_server *server, t_info *info)
{
    t_player *player;

    for (int i = 0; i < server->actual; i++) {
        if (clients[i].mode != GRAPHIQUE)
            player = get_player_by_id(clients[i].id, info);
        if ((clients[i].mode != GRAPHIQUE && clients[i]._quit == true) ||
            (clients[i].mode != GRAPHIQUE && player->ressource[FOOD] <= 0))
            remove_client(clients, i, server, info);
    }
    return;
}
