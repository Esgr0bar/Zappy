/*
** EPITECH PROJECT, 2023
** server
** File description:
** handle_command_graph
*/

#include "server.h"

static int func(t_client *client, int index, char **tab, t_info *info)
{
    static int (*function[15])(char **tab, t_client *c, t_info *info) = {
        msz, bct, mct, tna, ppo, plv, pin, sgt, sst
    };
    int res = 0;

    res = (*function[index])(tab, client, info);
    if (res == -1)
        return -1;
    return 0;
}

static int command(t_client *client, int error, t_info *info)
{
    static const char *f[15] = {"msz", "bct", "mct", "tna",
    "ppo", "plv", "pin", "sgt", "sst", NULL};
    char **tab = NULL;

    tab = my_str_to_word_array(client->_cmd, "\n ");
    for (int i = 0; f[i] != NULL ; i++) {
        if (tab[0] != NULL && strcasecmp(tab[0], f[i]) == 0) {
            error = func(client, i, tab, info);
            break;
        }
    }
    free_array(tab);
    return error;
}

int handle_command_graph(t_client *client, char *buffer, t_info *info)
{
    client->_cmd = strdup(buffer);
    command(client, 0, info);
    free(client->_cmd);
    client->_cmd = NULL;
    return 0;
}
