/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

/**
 * @file Map.hpp
 * @brief Map class header
 * 
 */

#include <vector>
#include <string>
#include <tuple>
#include "RaylibWrapper/raylib-cpp.hpp"

/**
 * @brief Namespace of the GUI
 * 
 */
namespace Gui {
    /**
     * @brief Map class
     * 
     */
    class Map {
    public:
        /* ---------------------------------- ENUM ---------------------------------- */
    
        /**
         * @brief Enum of the player orientation
         * 
         */
        enum e_orientation {
            NORTH = 1,                  //!< North orientation
            WEST = 2,                   //!< West orientation
            SOUTH = 3,                  //!< South orientation
            EAST = 4                    //!< East orientation
        };

        enum e_chatType {
            LEVEL_UP = 0,               //!< Level up message
            BROADCAST = 1,              //!< Broadcast message
            NEW_PLAYER = 2,             //!< New player message
            SERVER = 3,                 //!< Server message
            DEATH = 4,                  //!< Death message
            EGG = 5,                    //!< Egg layed message
            END = 6                     //!< End game message
        };

        /* ------------------------------- STRUCTURES ------------------------------- */

        /**
         * @brief Structure of a resource
         * 
         */
        typedef struct s_resources {
            int food;                   //!< Quantity of food
            int linemate;               //!< Quantity of linemate
            int deraumere;              //!< Quantity of deraumere
            int sibur;                  //!< Quantity of sibur  
            int mendiane;               //!< Quantity of mendiane
            int phiras;                 //!< Quantity of phiras
            int thystame;               //!< Quantity of thystame
        } t_resources;

        /**
         * @brief Structure of a tile
         * 
         */
        typedef struct s_tile {
            raylib::Vector3 position;   //!< Position of the tile
            bool selected;              //!< Is the tile selected
            t_resources resources;      //!< Resources of the tile
        } t_tile;

        /**
         * @brief Structure of an animated model
         * 
         */
        typedef struct s_anim {
            Model model;                //!< Model of the animation
            ModelAnimation *anim;       //!< Animation of the model
            int animCount;              //!< Animation count
            int animFrame;              //!< Animation frame
        } t_anim;

        /**
         * @brief Structure of a team
         * 
         */
        typedef struct s_teams {
            std::string name;           //!< Name of the team
            raylib::Color color;        //!< Color of the team
        } t_teams;

        /**
         * @brief Structure of a mouvement
         * 
         */
        typedef struct s_mouvement {
            raylib::Vector3 position;   //!< Initial position
            raylib::Vector3 newPosition;//!< New position
            bool isMoving;              //!< Is the player moving
        } t_mouvement;

        /**
         * @brief Structure of a player
         * 
         */
        typedef struct s_player {
            int id;                     //!< Id of the player
            t_mouvement mouvement;      //!< Mouvement of the player
            raylib::Vector3 rotation;   //!< Rotation of the player
            e_orientation orientation;  //!< Orientation of the player
            t_teams team;               //!< Team of the player
            t_anim anim;                //!< Animation of the player
            bool selected;              //!< Is the player selected
            t_resources inventory;      //!< Inventory of the player
            bool firstView;             //!< Is the player in first person view
            int level;                  //!< Level of the player
        } t_player;

        /* ------------------------------- PROTOTYPES ------------------------------- */

        /**
         * @brief Constructor of Map
         * 
         */
        Map();

        /**
         * @brief Destructor of Map
         * 
         */
        ~Map();

        /**
         * @brief Generate the map with the given parameters for each tile
         * 
         * @param x Tile at x position
         * @param y Tile at y position
         * @param food Quantity of food
         * @param linemate Quantity of linemate
         * @param deraumere Quantity of deraumere
         * @param sibur Quantity of sibur
         * @param mendiane Quantity of mendiane
         * @param phiras Quantity of phiras
         * @param thystame Quantity of thystame
         */
        void GenerateMap(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

        /**
         * @brief Init the camera
         * 
         */
        void InitCamera();

        /**
         * @brief Draw the map
         * 
         */
        void DrawMap();

        /**
         * @brief Add a player to the map
         * 
         * @param id Player's ID
         * @param x X position of the player
         * @param y Y position of the player
         * @param level Level of the player
         * @param orientation Orientation of the player
         * @param team Name of the team of the player
         */
        void AddPlayer(int id, float x, float y, int level, e_orientation orientation, std::string team);

        /**
         * @brief Create teams
         * 
         * @param teams Vector of all teams names
         */
        void CreateTeams(std::vector<std::string> teams);

        /**
         * @brief Update the player position
         * 
         * @param id ID of the player
         * @param x New X position of the player
         * @param y New Y position of the player
         * @param orientation New orientation of the player
         */
        void UpdatePlayerPosition(int id, float x, float y, e_orientation orientation);

        /**
         * @brief Update the player inventory
         * 
         * @param id ID of the player
         * @param food New quantity of food
         * @param linemate New quantity of linemate
         * @param deraumere New quantity of deraumere
         * @param sibur New quantity of sibur
         * @param mendiane New quantity of mendiane
         * @param phiras New quantity of phiras
         * @param thystame New quantity of thystame
         */
        void UpdatePlayerInventory(int id, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

        /**
         * @brief Update the player level
         * 
         * @param id ID of the player
         * @param level New level of the player
         */
        void UpdatePlayerLevel(int id, int level);

        /**
         * @brief Update the map tile with the given parameters
         * 
         * @param x X position
         * @param y Y position
         * @param food New quantity of food
         * @param linemate New quantity of linemate
         * @param deraumere New quantity of deraumere
         * @param sibur New quantity of sibur
         * @param mendiane New quantity of mendiane
         * @param phiras New quantity of phiras
         * @param thystame New quantity of thystame
         */
        void UpdateMapTile(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);
        
        /**
         * @brief Broadcast a message to all players
         * 
         * @param id ID of the player who sent the broadcast
         * @param message Message to broadcast
         */
        void BroadcastPlayer(int id, std::string message);

        /**
         * @brief Draw the menu
         * 
         */
        void DrawMenu();

        /**
         * @brief Animation of dead player
         * 
         * @param id ID of the player
         */
        void DeadPlayer(int id);

        /**
         * @brief Display the end game screen
         * 
         * @param team Name of the winning team
         */
        void EndGame(std::string team);

        /**
         * @brief Animation when a egg is layed
         * 
         * @param playerId ID of the player who laid the egg
         */
        void LayEgg(int playerId);

        /**
         * @brief Play the welcome sound
         * @details Ths function is required to be public because it is called in the main
         * 
         */
        void PlayWelcomeSound();

        /**
         * @brief Raylib window
         * 
         */
        raylib::Window _Window;

        /**
         * @brief Boolean to know if the menu has to be displayed
         * 
         */
        bool _InMenu;
    protected:
        /**
         * @brief Draw the ressources on the map
         * 
         * @param actualTile The tile to draw
         */
        void DrawRessources(int actualTile);

        /**
         * @brief Draw the players on the map
         * 
         * @param playerToDraw The player to draw
         */
        void DrawPlayers(int playerToDraw);

        /**
         * @brief Check if a tile is selected and display the ressources
         * 
         */
        void CheckTileSelection(int tileToCheck);

        /**
         * @brief Check if a player is selected and display the inventory
         * 
         * @param playerToCheck Player to check
         */
        void CheckPlayerSelection(int playerToCheck);

        /**
         * @brief Get absolute nbr value
         * 
         * @param nbr Nbr to convert
         * @return float Absolute result of nbr
         */
        float Absolue(float nbr);

        /**
         * @brief Compare two Vector3
         * 
         * @param v1 First vector to compare
         * @param v2 Second vector to compare
         * @return true Two vectors are the same
         * @return false Two vectors are different
         */
        bool CompareVector3(raylib::Vector3 v1, raylib::Vector3 v2);

        /**
         * @brief Reset the position of the camera
         * 
         */
        void ResetCamera();

        /**
         * @brief Draw chatbox
         * 
         */
        void DrawChat();

    private:
        std::vector<t_tile> _Tiles;

        raylib::Camera _Camera;
        bool _IsFirstView;
        raylib::Ray _Ray;
        raylib::RayCollision _TileCollision;
        raylib::RayCollision _PlayerCollision;

        std::vector<t_player> _Players;
        std::vector<t_teams> _Teams;

        raylib::Model _GrassModel;
        raylib::Texture _GrassTexture;

        raylib::AudioDevice _AudioDevice;
        raylib::Sound _WelcomeSound;
        raylib::Sound _LevelupSound;
        raylib::Sound _BroadcastSound;
        raylib::Sound _NewPlayerSound;
        raylib::Sound _EndGameSound;
        raylib::Sound _EggLayedSound;
        float _MasterVolume;

        std::vector<std::tuple<e_chatType, std::string>> _Chat;
    };
}

#endif /* !MAP_HPP_ */
