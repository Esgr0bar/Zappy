/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-jules.gresset
** File description:
** server
*/

/**
 * @file server.h
 * @brief This file contains all the structures and functions prototypes used in the server
 * 
 */

#ifndef SERVER_H_
    #define SERVER_H_

    #include <stdio.h>
    #include <ctype.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netdb.h>
    #include <stdlib.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <string.h>
    #include <arpa/inet.h>
    #include <sys/wait.h>
    #include <stdbool.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <sys/wait.h>
    #include <uuid/uuid.h>
    #include <sys/stat.h>
    #include <string.h>
    #include <time.h>
    #include <signal.h>

    #include "ressources.h"

    /**
     * @brief Macro to get the square of a number
     * 
     */
    #define square(a) (a)*(a)

    /**
     * @brief Macro to get the absolute value of a number
     * 
     */
    #define ABS(x)	(x < 0 ? -x : x)


/**
 * @brief Struct for the server
 * 
 */
typedef struct s_server {
    int _fd_srv;    //!< fd server
    int fd_graph;   //!< fd client graphic
    int _port;      //!< port to listen
    struct sockaddr_in addr;    //!< struct addr
    socklen_t size; //!< struct for select
    fd_set rdfs; //!< array of fd
    int max;    //!< max fd
    int actual; //!< max client
    int width;  //!< width map
    int height; //!< height map
    int client_nb; //!< number client on the server
    int freq; //!< freq use for calculate unit time
    char **name_team; //!< array of all name team
} t_server;

/**
 * @brief Struct for the client
 * 
 */
typedef struct s_client {
    int _fd; //!< fd of the current client
    char *_name_team; //!< name of a team
    char *_buffer; //!< buffer for stock cmd before execute
    char *_cmd; //!< buffer stock for cmd on waiting
    int _nb_cmd; //!< number of waiting cmd
    int _quit;  //!< if client quit or not
    int _log;   //!< if the client is log
    struct sockaddr_in _addr; //!< struct addr
    socklen_t _size; //!< struct for select
    clock_t time_cmd; //!< time of the last action
    clock_t time_life; //!< time of the last life
    int mode; //!< mode player or graphic
    int id; //!< id of the client when is connected
    int count_life; //!< number of unit time for decremente unit life
    int count_cmd; //!< number of unit time for execute another action
} t_client;

/**
 * @brief Struct for the arguments
 * 
 */

typedef struct s_args {
    int freq; //!< freq use for calculate unit time
    int width; //!< width map
    int height; //!< height map
    int clientNb; //!< number client limit par team
    int port; //!< port to listen
    char **name_team; //!< array of all name team
} t_args;

/**
 * @brief Struct for the map
 * 
 */
typedef struct s_map {
    int x; //!< width map
    int y; //!< height map
    int nb_player; //!< number of player in the tile
    int *ressources; //!< array of ressources in the tile
} t_map;

/**
 * @brief Struct for the player
 * 
 */
typedef struct s_player {
    int x; //!< pos on x in the map
    int y; //!< pos on y in the map
    int O; //!< orientation of the player
    int level; //!< level of the player
    int *ressource; //!< inventory of ressources of the player
    int fd; //!< socket fd for write to the client control the player
    int id; //!< id for find the player by the id of the client
    int end; //!< int represent the end of th array of this struct
} t_player;

/**
 * @brief Struct for the team
 * 
 */
typedef struct s_team {
    char *name; //!< name of the team
    int *id; //!< all  id of player in the team
    int nb_client; //!< number slot free in the team
    int count; //!< number slot already take
    int end; //!< number for parse the array of team
} t_team;

/**
 * @brief Struct for the info of the server
 * 
 */
typedef struct s_info {
    int x; //!< width of the map
    int y; //!< height of the map
    int nb_player; //!< number of player on the map
    char **name_team; //!< array of all name team
    t_map **map; //!< array of all tile of the map
    int freq; //!< freq use for calculate unit time
    int *max_ressources; //!< array of the max ressource spawn
    int size_map; //!< number of tiles
    clock_t time_respawn; //!< time use for respawn ressources
    t_player *player; //!< array of all player
    int count_id; //!< use for id of all player
    int fd_graph; //!< socket fd of the client graph
    t_team *team; //!< array of all teams
} t_info;

/**
 * @brief Struct for the orientation
 * 
 */
typedef struct s_orientation {
    int O; //!< orientation
    int up_left; //!< tile up left
    int up_right; //!< tile up right
    int up_center; //!< tile up center
    int down_left; //!< tile down left
    int down_right; //!< tile down right
    int down_center; //!< tile down center
    int center_left; //!< tile center left
    int center_right; //!< tile center right
} t_orientation;

/**
 * @brief fill the struct server with argument and init the socket
 *
 * @param server struct server
 * @param argv all argument
 * @return return 0 if init it's ok else return -1
 */
int init_server(t_server *server, char **argv);

/**
 * @brief fill struct args with all string argument
 *
 * @param args struct argument
 * @param argv array of argument
 * @return return 0 if fill struct it's ok else return -1
 */
int parse_args(t_args *args, char **argv);

/**
 * @brief handle all socket connect on server and accept new socket
 *
 * @param server struct with all information for the server
 * @param info struct with all information for the server
 */
void handle_server(t_server *server, t_info *info);

/**
 * @brief init new client
 *
 * @param clients array clients
 * @param server struct with all information for the server
 * @param c struct new client
 */
void init(t_client *clients, t_server *server, t_client c);

/**
 * @brief remove client to the server
 *
 * @param clients array clients
 * @param index index into the array
 * @param server struct with all information for the server
 * @param info struct with all information for the server
 */
void remove_client(t_client *clients, int index,
    t_server *server, t_info *info);

/**
 * @brief check if client is disconnect
 *
 * @param clients array clients
 * @param server struct with all information for the server
 * @param info struct with all information for the server
 */
void delete_client(t_client *clients, t_server *server, t_info *info);

/**
 * @brief check fd_isset
 *
 * @param clients array clients
 * @param i index array clients to check
 * @param server struct with all information for the server
 * @param info struct with all information for the server
 */
void check_client(t_client *clients, int i, t_server *server, t_info *info);

/**
 * @brief function for free all struct information in end of the program
 *
 * @param server struct with all information for the server
 * @param info struct with all information for the server
 */
void free_all(t_server *server, t_info *info);

/**
 * @brief function for free an array of char
 *
 * @param tmp array of char
 */
void free_array(char **tmp);

/**
 * @brief check and run command after read in the fd of a client
 *
 * @param client client reading command
 * @param buffer command
 * @param info struct with all information for the server
 * @return return 0 if i execute command else return -1
 */
int handle_command_ia(t_client *client, char *buffer, t_info *info);

/**
 * @brief function for split a char * into char ** with delimiters
 *
 * @param str array to split
 * @param delim string of delimiters
 * @return return char ** split by delimiters
 */
char **my_str_to_word_array(char *str, char *delim);

/**
 * @brief function init map and init struct info
 *
 * @param server all info for communication
 * @param info all info for the game
 * @return return 0 if no error else return -1
 */
int init_info(t_server *server, t_info *info);

/**
 * @brief function to count the number of N resources on the map
 *
 * @param info all info for the game
 * @param ressource Ressource to count
 * @return int number of N resources on the map
 */
int count_ressources(t_info *info, int ressource);

/**
 * @brief function to generate the ressources on the map,
 * to call every 20 units of time
 *
 * @param info all info for the game
 */
void generate_ressources(t_info *info);

/**
 * @brief update timer for action client and respawn ressource
 * @param info struct with all info game
 * @param clients struct with all info about client
 * @param server struct with all info about server
 * @return return 0 if no error else return -1
 */

int update_time(t_info *info, t_client *clients, t_server *server);

/**
 * @brief print all object in the tile
 *
 * @param buffer buffer to print
 * @param map tile of the map
 * @return char* return buffer of the tile
 */

char *print_tile(char *buffer, t_map *map);

/**
 * @brief algo for the cmd look
 *
 * @param client client who send cmd
 * @param info all info of the game
 * @return char* return buffer of the tile
 */

char *algo_look(t_client *client, t_info *info);

/**
 * @brief Create a player object
 *
 * @param clients all clients
 * @param server all info for the networking
 * @param info all info of the game
 * @return int return 0 if no error else return -1
 */
int create_player(t_client *clients, t_server *server, t_info *info);

/**
 * @brief Get the player object
 *
 * @param client client
 * @param info all info of the game
 * @return t_player* return player
 */
t_player *get_player(t_client *client, t_info *info);

/**
 * @brief generate random int with limit
 *
 * @param limit number limit
 * @return int
 */
int random_int(int limit);

/**
 * @brief detected who is connected
 *
 * @param fd fd of the new client
 * @param client all client
 * @param server all info of the networking
 * @param info all info of the game
 * @return int
 */
int init_connection(int fd, t_client *client, t_server *server, t_info *info);

/**
 * @brief handle all cmd graph
 *
 * @param client client who send cmd
 * @param buffer cmd
 * @param info all info of the game
 * @return int
 */
int handle_command_graph(t_client *client, char *buffer, t_info *info);

/**
 * @brief command msz for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int msz(char **tab, t_client *client, t_info *info);

/**
 * @brief command bct for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int bct(char **tab, t_client *client, t_info *info);

/**
 * @brief command mct for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int mct(char **tab, t_client *client, t_info *info);

/**
 * @brief command tna for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int tna(char **tab, t_client *client, t_info *info);

/**
 * @brief command ppo for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int ppo(char **tab, t_client *client, t_info *info);

/**
 * @brief command plv for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int plv(char **tab, t_client *client, t_info *info);

/**
 * @brief command pin for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int pin(char **tab, t_client *client, t_info *info);

/**
 * @brief command sst for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int sst(char **tab, t_client *client, t_info *info);

/**
 * @brief command sgt for client graphic
 *
 * @param tab all argument for the cmd
 * @param client client graphic
 * @param info all info of the game
 * @return return 0 if no error else return -1
 */
int sgt(char **tab, t_client *client, t_info *info);

/**
 * @brief Get the player by id client
 *
 * @param id id of the client
 * @param info all info of the game
 * @return t_player*
 */
t_player *get_player_by_id(int id, t_info *info);

/**
 * @brief Get the player pos object
 *
 * @param player current player
 * @param info  all info of the game
 * @return int
 */
int get_player_pos(t_player *player, t_info *info);

/**
 * @brief command broadcast for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int broadcast(char **tab, t_client *c, t_info *info);

/**
 * @brief command connect_nbr for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int connect_nbr(char **tab, t_client *c, t_info *info);

/**
 * @brief command eject for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int eject(char **tab, t_client *c, t_info *info);

/**
 * @brief command fork for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int fork_ia(char **tab, t_client *c, t_info *info);

/**
 * @brief command forward for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int forward(char **tab, t_client *c, t_info *info);

/**
 * @brief command incantation for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int incantation(char **tab, t_client *c, t_info *info);

/**
 * @brief command inventory for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int inventory(char **tab, t_client *c, t_info *info);

/**
 * @brief command left for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int left_ia(char **tab, t_client *c, t_info *info);

/**
 * @brief command look for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int look(char **tab, t_client *c, t_info *info);

/**
 * @brief command right for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int right_ia(char **tab, t_client *c, t_info *info);

/**
 * @brief command set for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int set(char **tab, t_client *c, t_info *info);

/**
 * @brief command take for client ia
 *
 * @param tab rest of commands in case the command takes argument
 * @param c client of the ia
 * @param info of the game
 * @return error
 */
int take(char **tab, t_client *c, t_info *info);

/**
 * @brief Get the player id object
 *
 * @param c player client
 * @param info all server info
 * @return id of player
 */
int get_player_id(t_client *c, t_info *info);

/**
 * @brief algo for the cmd broadcast
 *
 * @param p player who send msg
 * @param t player who receive msg
 * @param info all info of the game
 * @return int
 */
int algo_broadcast(t_player *p, t_player *t, t_info *info);

/**
 * @brief add two buffers dynamically
 *
 * @param buffer the buffer who is alloc dynamically
 * @param tmp the buffer who want to add to the buffer original
 * @return char*
 */
char *realloc_buffer(char *buffer, char *tmp);

/**
 * @brief handle all cmd ia
 *
 * @param client client who send cmd
 * @param buffer cmd
 * @param info all info of the game
 * @return int
 */
int handle_command_ia(t_client *client, char *buffer, t_info *info);

/**
 * @brief delete all client when the server is kill
 *
 * @param clients all clients
 * @param server all information for networking
 * @param info all info of the game
 */
void delete_all_client(t_client *clients, t_server *server, t_info *info);

/**
 * @brief free all player
 *
 * @param player array of all player
 */
void free_player(t_player *player);

/**
 * @brief free all team
 *
 * @param team array of all team
 */
void free_team(t_team *team);

/**
 * @brief for elevate level of all player who start incantation
 *
 * @param c client
 * @param info all info of the game
 * @param id id of the player
 * @return int
 */
int elevation(t_client *c, t_info *info, int id);

/**
 * @brief realloc int *
 *
 * @param ressources array of ressource
 * @return int*
 */
int *realloc_ressource(int *ressources);

/**
 * @brief check for write into fd
 *
 * @param fd fd to a client
 * @return int return 0 if no error else return -1
 */
int write_into_fd(int fd);

/**
 * @brief use for break loop²
 *
 * @param handle use manage function
 * @param new init var
 * @return int return var
 */
int send_int(int handle, int new);


/**
 * @brief use for check index in look
 *
 * @param index index in the map
 * @param info info of all the game
 */
void check_index(int *index, t_info *info);

#endif /* !SERVER_H_ */
