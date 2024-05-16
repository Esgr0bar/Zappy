/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** ressources.h
*/

/**
 * @file ressources.h
 * @brief This file contains all the macros used in the server
 * 
 */

#ifndef _RESSOURCES_
    #define _RESSOURCES_

/**
 * @brief Macros used to find the place of the food resource in an int array
 *
 */
static const int FOOD = 0;
/**
 * @brief Macros used to find the place of the linemate resource in
 * an int array
 *
 */
static const int LINEMATE = 1;
/**
 * @brief Macros used to find the place of the deraumere resource
 * in an int array
 *
 */
static const int DERAUMERE = 2;
/**
 * @brief Macros used to find the place of the sibur resource in an int array
 *
 */
static const int SIBUR = 3;
/**
 * @brief Macros used to find the place of the mendiane resource in
 * an int array
 *
 */
static const int MENDIANE = 4;
/**
 * @brief Macros used to find the place of the phiras resource in an int array
 *
 */
static const int PHIRAS = 5;
/**
 * @brief Macros used to find the place of the thystame resource in
 * an int array
 *
 */
static const int THYSTAME = 6;

/**
 * @brief Tab macro used to know the resources needed for each level of
 * elevation in the incantation
 *
 */
static const int ELEVATION[7][7] = {{1, 1, 0, 0, 0, 0, 0},
                                    {2, 1, 1, 1, 0, 0, 0},
                                    {2, 2, 0, 1, 0, 2, 0},
                                    {4, 1, 1, 2, 0, 1, 0},
                                    {4, 1, 2, 1, 3, 0, 0},
                                    {6, 1, 2, 3, 0, 1, 0},
                                    {6, 2, 2, 2, 2, 2, 1}};

/**
 * @brief Macros for the density of food
 *
 */
static const float DEN_FOOD = 0.5;
/**
 * @brief Macros for the density of linemate
 *
 */
static const float DEN_LINEMATE = 0.3;
/**
 * @brief Macros for the density of deraumere
 *
 */
static const float DEN_DERAUMERE = 0.15;
/**
 * @brief Macros for the density of sibur
 *
 */
static const float DEN_SIBUR = 0.1;
/**
 * @brief Macros for the density of mendiane
 *
 */
static const float DEN_MENDIANE = 0.1;
/**
 * @brief Macros for the density of phiras
 *
 */
static const float DEN_PHIRAS = 0.08;
/**
 * @brief Macros for the density of thystame
 *
 */
static const float DEN_THYSTAME = 0.05;

/**
 * @brief total numbers of resources
 *
 */
static const int NB_RESSOURCES = 7;

/**
 * @brief Unit of time needed for each resources respawn
 *
 */
static const int RESPAWN_RESSOURCES_UNIT = 20;

/**
 * @brief Macros for up direction
 *
 */
static const int UP = 0;
/**
 * @brief Macros for right direction
 *
 */
static const int RIGHT = 1;
/**
 * @brief Macros for back direction
 *
 */
static const int BACK = 2;
/**
 * @brief Macros for left direction
 *
 */
static const int LEFT = 3;

/**
 * @brief Macros used to know if a graphic client is connected to the server
 *
 */
static const int GRAPHIQUE = 1;
/**
 * @brief Macros used to know if an ai client is connected to the server
 *
 */
static const int PLAYER = 0;

/**
 * @brief Unit of time needed for the forward server command
 *
 */
static const int FORWARD = 7;
/**
 * @brief Unit of time needed for the right server command
 *
 */
static const int RIGHT_CMD = 7;
/**
 * @brief Unit of time needed for the left server command
 *
 */
static const int LEFT_CMD = 7;
/**
 * @brief Unit of time needed for the look server command
 *
 */
static const int LOOK = 7;
/**
 * @brief Unit of time needed for the inventory server command
 *
 */
static const int INVENTORY = 1;
/**
 * @brief Unit of time needed for the broadcast server command
 *
 */
static const int BROADCAST = 7;
/**
 * @brief Unit of time needed for the fork server command
 *
 */
static const int FORK = 42;
/**
 * @brief Unit of time needed for the eject server command
 *
 */
static const int EJECT = 7;
/**
 * @brief Unit of time needed for the take server command
 *
 */
static const int TAKE = 7;
/**
 * @brief Unit of time needed for the set server command
 *
 */
static const int SET = 7;
/**
 * @brief Unit of time needed for the incantation server command
 *
 */
static const int INCANTATION = 300;

/**
 * @brief Time before a player is killed
 *
 */
static const int TIME_LIFE = 126;

#endif
