/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** write_into_fd
*/

#include "server.h"

static void set_all_fds(int fd, fd_set *write_fds)
{
    FD_ZERO(write_fds);
    FD_SET(fd, write_fds);
}

int write_into_fd(int fd)
{
    fd_set write_fds;
    struct timeval timeout;
    int result = 0;

    set_all_fds(fd, &write_fds);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    result = select(fd + 1, NULL, &write_fds, NULL, &timeout);
    if (result == -1) {
        return -1;
    } else if (result == 0) {
        return -1;
    } else {
        if (FD_ISSET(fd, &write_fds))
            return 0;
        else
            return -1;
    }
}
