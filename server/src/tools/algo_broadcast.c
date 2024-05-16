/*
** EPITECH PROJECT, 2023
** server
** File description:
** algo_broadcast
*/

#include <math.h>
#include "server.h"

static const t_orientation ORIENTATION[] = {
    {UP, 2, 8, 1, 4, 6, 5, 3, 7},
    {RIGHT, 4, 2, 3, 6, 8, 7, 5, 1},
    {BACK, 6, 4, 5, 8, 2, 1, 7, 3},
    {LEFT, 8, 6, 7, 2, 4, 3, 1, 5}
};

int get_distance(double *size_player, double *size_target, double *size_map)
{
    double x1 = size_target[0] - size_player[0];
    double x2 = size_map[0] - ABS(x1);
    double y1 = size_target[1] - size_player[1];
    double y2 = size_map[1] - ABS(y1);
    double x = size_player[0] < size_target[0] ? 1 :
        size_player[0] > size_target[0] ? -1 : 0;
    double y = size_player[1] < size_target[1] ? 1 :
        size_player[1] > size_target[1] ? -1 : 0;
    int orientation = 0;
    double distance[2];

    if (ABS(x2) < ABS(x1))
        x *= (-1);
    if (ABS(y2) < ABS(y1))
        y *= (-1);
    distance[0] = x;
    distance[1] = y;
    orientation += distance[0] == 1 ? 1 : distance[0] == -1 ? 2 : 3;
    orientation += distance[1] == 1 ? 10 : distance[1] == -1 ? 20 : 30;
    return orientation;
}

static int choose_nb(int orientation, int index, int O)
{
    for (;ORIENTATION[index].O != O; index++);
    switch (orientation) {
        case (11):
            return (ORIENTATION[index].up_left);
        case (21):
            return (ORIENTATION[index].down_left);
        case (31):
            return (ORIENTATION[index].center_left);
        case (12):
            return (ORIENTATION[index].up_right);
        case (22):
            return (ORIENTATION[index].down_right);
        case (32):
            return (ORIENTATION[index].center_right);
        case (13):
            return (ORIENTATION[index].up_center);
        case (23):
            return (ORIENTATION[index].down_center);
    }
    return 0;
}

int algo_broadcast(t_player *p, t_player *t, t_info *info)
{
    int orientation = 0;
    double player[2] = {p->x, p->y};
    double target[2] = {t->x, t->y};
    double size_map[2] = {info->x, info->y};

    orientation = get_distance(player, target, size_map);
    orientation = choose_nb(orientation, 0, t->O);
    return orientation;
}
