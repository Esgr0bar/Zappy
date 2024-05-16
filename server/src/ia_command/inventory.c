/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** inventory.c
*/

#include "server.h"

char *add_to_str(char *base, char *add)
{
    static int tmp = 0;

    if (tmp != 0)
        base = realloc_buffer(base, ", ");
    else
        tmp++;
    base = realloc_buffer(base, add);
    return base;
}

char *get_resource_nbr(t_client *c, t_info *info, int rsc, char *rsc_name)
{
    int i = 0;
    char *new = calloc(sizeof(char), 1);
    char nbr[10];

    for (i = 0; i < info->nb_player; i++) {
        if (info->player[i].id == c->id)
            break;
    }
    sprintf(nbr, "%d", info->player[i].ressource[rsc]);
    new = realloc_buffer(new, rsc_name);
    new = realloc_buffer(new, " ");
    new = realloc_buffer(new, nbr);
    return new;
}

char *get_inventory_str(t_client *c, t_info *info)
{
    char *tab[7] = {"food", "linemate", "deraumere", "sibur",
        "mendiane", "phiras", "thystame"};
    char *str = calloc(sizeof(char), 1);
    char *temp = NULL;

    for (int i = 0; i < NB_RESSOURCES; i++) {
        temp = get_resource_nbr(c, info, i, tab[i]);
        if (temp != NULL)
            str = add_to_str(str, temp);
        free(temp);
    }
    return str;
}

int inventory(char **tab, t_client *c, t_info *info)
{
    char *inventory_str = get_inventory_str(c, info);

    (void)tab;
    if (write_into_fd(c->_fd) == 0)
        dprintf(c->_fd, "[%s]\n", inventory_str);
    free(inventory_str);
    c->count_cmd = INVENTORY;
    c->time_cmd = clock();
    return 0;
}
