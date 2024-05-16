##
## EPITECH PROJECT, 2023
## B-YEP-400-PAR-4-1-zappy-jules.gresset
## File description:
## Makefile
##

SRC	=	src/handle_server.c	\
		src/delete_client.c	\
		src/check.c	\
		src/handle_command_graph.c	\
		src/handle_command_ia.c	\
		src/check_time.c	\
		src/create_new_player.c	\
		src/kill_server.c	\
		src/init/init.c	\
		src/init/init_map.c	\
		src/init/init_server.c	\
		src/tools/my_str_to_word_array.c	\
		src/tools/count_ressources.c	\
		src/tools/generate_ressources.c	\
		src/tools/parse_args.c	\
		src/tools/algo_look.c	\
		src/tools/algo_look_bis.c	\
		src/tools/algo_broadcast.c	\
		src/tools/get_tile.c	\
		src/tools/random_int.c	\
		src/tools/get_player.c	\
		src/tools/init_connection.c	\
		src/tools/buffering.c	\
		src/tools/write_into_fd.c	\
		src/tools/get_player_pos.c	\
		src/free_memory/free_memory.c	\
		src/cmd_client_graphic/msz.c	\
		src/cmd_client_graphic/bct.c	\
		src/cmd_client_graphic/mct.c	\
		src/cmd_client_graphic/tna.c	\
		src/cmd_client_graphic/ppo.c	\
		src/cmd_client_graphic/plv.c	\
		src/cmd_client_graphic/sgt.c	\
		src/cmd_client_graphic/sst.c	\
		src/cmd_client_graphic/pin.c	\
		src/ia_command/broadcast.c		\
		src/ia_command/connect_nbr.c	\
		src/ia_command/eject.c			\
		src/ia_command/fork.c			\
		src/ia_command/forward.c		\
		src/ia_command/incantation.c	\
		src/ia_command/inventory.c		\
		src/ia_command/left.c			\
		src/ia_command/look.c			\
		src/ia_command/right.c			\
		src/ia_command/set.c			\
		src/ia_command/take.c			\
		src/ia_command/get_player_id.c	\
		src/main.c


CC = gcc

CFLAGS = -Wall -Wextra -g3

CPPFLAG = -I ./include/

NAME = zappy_server

all:
	$(CC) -o $(NAME) $(SRC) $(CPPFLAG) $(CFLAGS)
clean:
	$(RM) *.gc*

fclean: clean
	$(RM) $(NAME)

debug: CFLAGS += -g3
debug: re

re: fclean all

.PHONY: all clean fclean debug re
