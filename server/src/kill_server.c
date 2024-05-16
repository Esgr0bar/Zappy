/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** kill_server
*/

#include "server.h"

int send_int(int handle, int new)
{
    static int var = 0;

    if (handle == 0)
        return var;
    else {
        var = new;
        return var;
    }
    return var;
}
