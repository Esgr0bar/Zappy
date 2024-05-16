/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

/**
 * @file Server.hpp
 * @brief Server class header
 * 
 */

#include "Map.hpp"
#include <stdio.h>
#include <tuple>
#include <vector>
#include <sys/socket.h>
#include <sstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<arpa/inet.h>
#include<netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <exception>

namespace Gui {
    /**
     * @brief Server class
     * 
     */
    class Server {
    public:
        /**
         * @brief Construct a new Server object
         * 
         */
        Server();

        /**
         * @brief Destroy the Server object
         * 
         */
        ~Server();

        /**
         * @brief Listen server waiting for a command
         * 
         */
        void ListenServer();
        
        /**
         * @brief Connect to zappy server
         * @param port         
        */
        int ConnectServer(int port, std::string ip);

        /**
         * @brief send a command to the server
         * 
         * @param command 
         * @return int 
         */
        int SendCommand(std::string command);

        /**
         * @brief print the result of what the server send
         * 
         * @return std::string
         */
        std::string ReceiveCommand();

        /**
         * @brief print the result of what the server send without blocking
         * 
         * @return std::string
         */
        std::string ReceiveCommandNonBlock();

        /**
         * @brief Get the map from the server
         * 
         */
        void GetMap();

        /**
         * @brief Get the content of a tile
         * 
         * @param x X position of the tile
         * @param y Y position of the tile
         */
        void ContentTile(int x, int y);

        /**
         * @brief get the position of a player
         * @param player nbr
         */
        void PlayerPosition(std::string player);

        /**
         * @brief get the inventory of a player
         * @param player nbr
         */
        void PlayerInventory(std::string player);
        
        /**
         * @brief get the level of a player
         * @param player nbr
         */
        void PlayerLevel(std::string player);
        
        /**
         * @brief get the name of all the teams
         */
        void NameTeam();
        
        /**
         * @brief get all the map
         *  
         */
        void GetAllMap();
        
        /**
         * @brief get the time unit of the server
         */
        void TimeUnit();
        
        /**
         * @brief modify the time unit of the server
         * @param time
         * @return int 
         */
        void TimeUnitModification(int time);

        /**
         * @brief Find PNW command in a buffer
         * 
         * @param command Buffer to inspect
         */
        void findPnw(std::string command);
        
        /**
         * @brief Vector of all the map
         * 
         */
        std::vector<int> _map;

        /**
         * @brief Vector of all the tiles
         * 
         */
        std::vector<int> _tile;

        /**
         * @brief Vector of all the teams name
         * 
         */
        std::vector<std::string> _team;

        /**
         * @brief Vector of all the player
         * 
         */
        std::vector<int> _player;

        /**
         * @brief Map GUI object
         * 
         */
        Gui::Map _Map;
    protected:
        int _sockfd;
    };
}

#endif /* !SERVER_HPP_ */
