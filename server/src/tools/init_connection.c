/*
** EPITECH PROJECT, 2023
** server
** File description:
** read_client
*/

#include "server.h"

int check_team(char *buffer, t_info *info, t_client *client)
{
    (void)client;
    for (int i = 0; info->team[i].end != 1; i++) {
        if (strcmp(info->team[i].name, buffer) == 0
            && info->team[i].nb_client != 0) {
            info->team[i].id[info->team[i].count] = info->count_id;
            info->team[i].count++;
            info->team[i].nb_client--;
            return 0;
        }
    }
    close(client->_fd);
    return -1;
}

static int init_connection_bis(int index, t_client *client,
    t_info *info, char *buffer)
{
    client->_name_team = strdup(buffer);
    client->mode = PLAYER;
    dprintf(client->_fd, "%d\n%d %d\n",
    info->team[index].nb_client, info->x, info->y);
    free(buffer);
    return 1;
}

int init_connection(int fd, t_client *client, t_server *server, t_info *info)
{
    char *buffer = malloc(sizeof(char) * 1024);
    int error = 0;

    if (write_into_fd(fd) != 0)
        return -1;
    dprintf(fd, "WELCOME\n");
    error = read(fd, buffer, 1024);
    buffer[error - 1] = '\0';
    if (strcmp(buffer, "GRAPHIC") == 0) {
        server->fd_graph = fd;
        client->mode = GRAPHIQUE;
        client->_name_team = NULL;
        free(buffer);
        return error;
    }
    if ((error = check_team(buffer, info, client)) == -1) {
        free(buffer);
        return -1;
    }
    return init_connection_bis(error, client, info, buffer);
}
