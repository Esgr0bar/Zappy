/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** main
*/

#include "server.h"

static int display_help(int value)
{
    printf("USAGE: ./zappy_server -p port -x width -y height ");
    printf("-n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n\twidth\tis the width of the world\n");
    printf("\theight\tis the height of the world\n\tnameX\tis ");
    printf("the name of the team ");
    printf("X\n\tclientNb\t is the number of authorized clients per team\n\t");
    printf("freq\tis the reciprocal of time unit for execution of actions\n");
    return value;
}

int main(int argc, char **argv)
{
    t_server *server;
    t_info *info;

    if (argv[1] != NULL && strcmp(argv[1], "-help") == 0)
        return display_help(0);
    if (argc == 1)
        return display_help(84);
    server = malloc(sizeof(t_server));
    if (init_server(server, argv) == -1) {
        free(server);
        return 84;
    }
    info = malloc(sizeof(t_info) * 1);
    init_info(server, info);
    handle_server(server, info);
    free_all(server, info);
    return 0;
}
