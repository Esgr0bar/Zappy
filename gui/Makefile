##
## EPITECH PROJECT, 2023
## B-YEP-400-PAR-4-1-zappy-jules.gresset
## File description:
## Makefile
##

UNAME := $(shell uname)

SRC	=	src/Main.cpp				\
		src/Map.cpp					\
		src/Server.cpp


CC = g++

CFLAG = -Wall -Wextra

CPPFLAG = -std=c++2a -I ./include/

NAME = zappy_gui

ifeq ($(UNAME), Linux)
	CPPFLAG += -lraylib -lGL -lm -pthread -ldl -lrt -lX11
endif
ifeq ($(UNAME), Darwin)
	CPPFLAG += `pkg-config --libs --cflags raylib`
endif

all:
	$(CC) -o $(NAME) $(SRC) $(CFLAG) $(CPPFLAG) -g3
clean:
	$(RM) *.gc*

fclean: clean
	$(RM) $(NAME)

debug: $(CPPFLAG) += -g3
debug: re

re: fclean all

.PHONY: all clean fclean debug re