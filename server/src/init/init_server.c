/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** init_server
*/

#include "server.h"

static int fill_struct(t_server *server, t_args *args)
{
    server->_port = htons(args->port);
    server->_fd_srv = socket(AF_INET, SOCK_STREAM, 0);
    if (server->_fd_srv == -1)
        return -1;
    server->size = sizeof(server->addr);
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = server->_port;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->actual = 0;
    server->max = server->_fd_srv;
    server->width = args->width;
    server->height = args->height;
    server->freq = args->freq;
    server->client_nb = args->clientNb;
    server->name_team = args->name_team;
    server->fd_graph = -1;
    return 0;
}

static int init_server_bis(t_server *server)
{
    int debug = 0;

    if (setsockopt(server->_fd_srv, SOL_SOCKET, SO_REUSEADDR,
    &debug, sizeof(int)) == -1)
        return -1;
    if (bind(server->_fd_srv, (struct sockaddr *) &server->addr,
    sizeof(server->addr)) == -1) {
        if (close(server->_fd_srv) == -1)
            return -1;
        return -1;
    }
    if (listen(server->_fd_srv, 100) == -1) {
        if (close(server->_fd_srv) == -1)
            return -1;
        return -1;
    }
    return 0;
}

int init_server(t_server *server, char **argv)
{
    t_args *args = malloc(sizeof(t_args) * 1);

    if (parse_args(args, argv) == -1) {
        free(args);
        return -1;
    }
    if (fill_struct(server, args) == -1) {
        free(args);
        return -1;
    }
    free(args);
    return init_server_bis(server);
}
