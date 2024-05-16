/*
** EPITECH PROJECT, 2023
** my_ftp
** File description:
** init
*/

#include "server.h"

void init(t_client *clients, t_server *server, t_client c)
{
    clients[server->actual] = c;
    clients[server->actual]._quit = false;
    clients[server->actual]._buffer = NULL;
    clients[server->actual]._cmd = NULL;
    clients[server->actual]._nb_cmd = 0;
    clients[server->actual]._log = -1;
    clients[server->actual].time_cmd = clock();
    clients[server->actual].time_life = clock();
    clients[server->actual].count_cmd = 0;
    clients[server->actual].count_life = 10;
}
