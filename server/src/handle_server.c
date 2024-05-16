/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** handle_server
*/

#include "server.h"

static void close_handler(int i)
{
    send_int(1, 1);
    (void) i;
}

static void read_client(t_server *server, t_client *clients, t_info *info)
{
    for (int i = 0; i < server->actual; i++)
        check_client(clients, i, server, info);
}

static void init_socket_client(fd_set *rdfs, t_client *clients,
int actual, t_server *server)
{
    FD_ZERO(&server->rdfs);
    FD_SET(server->_fd_srv, &server->rdfs);
    for (int i = 0; i < actual; ++i)
        FD_SET(clients[i]._fd, rdfs);
}

static void new_client(t_client *clients, t_server *server, t_info *info)
{
    struct sockaddr_in csin = { 0 };
    socklen_t size = sizeof(csin);
    t_client c;

    c._fd = accept(server->_fd_srv, (struct sockaddr *)&csin, &size);
    if (init_connection(c._fd, &c, server, info) == -1) {
        close(c._fd);
        return;
    }
    server->max = c._fd > server->max ? c._fd : server->max;
    FD_SET(c._fd, &server->rdfs);
    init(clients, server, c);
    clients[server->actual].id = info->count_id;
    if (clients[server->actual].mode != GRAPHIQUE) {
        create_player(clients, server, info);
        info->nb_player++;
        info->count_id++;
    } else
        info->fd_graph = server->fd_graph;
    server->actual++;
}

void handle_server(t_server *server, t_info *info)
{
    t_client clients[100];
    struct timeval timeout = {1, 0};

    signal(SIGINT, close_handler);
    while (send_int(0, 0) == 0) {
        init_socket_client(&server->rdfs, clients, server->actual, server);
        if (select(server->max + 1, &server->rdfs,
            NULL, NULL, &timeout) == -1) {
            close(server->_fd_srv);
            break;
        }
        update_time(info, clients, server);
        if (FD_ISSET(server->_fd_srv, &server->rdfs))
            new_client(clients, server, info);
        else {
            read_client(server, clients, info);
            delete_client(clients, server, info);
        }
    }
    delete_all_client(clients, server, info);
}
