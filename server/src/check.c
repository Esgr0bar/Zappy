/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** check
*/

#include "server.h"

static void check_read(t_client *clients, int i, t_server *server,
t_info *info)
{
    char *buffer = malloc(sizeof(char) * 1024);
    int error;

    error = read(clients[i]._fd, buffer, 1024);
    if (error == 0) {
        close(clients[i]._fd);
        remove_client(clients, i, server, info);
        free(buffer);
    } else if (error == -1) {
        perror("read()");
        free(buffer);
        return;
    } else {
        buffer[error] = '\0';
        if (clients[i].mode == GRAPHIQUE)
            handle_command_graph(&clients[i], buffer, info);
        else
            handle_command_ia(&clients[i], buffer, info);
        free(buffer);
    }
}

void check_client(t_client *clients, int i, t_server *server, t_info *info)
{
    if (FD_ISSET(clients[i]._fd, &server->rdfs) && clients[i].count_cmd == 0)
        check_read(clients, i, server, info);
}
