##
## EPITECH PROJECT, 2023
## B-YEP-400-PAR-4-1-zappy-jules.gresset
## File description:
## Makefile
##

SRC =		Main.py

NAME =		zappy_ai

all: $(NAME)

$(NAME):
	cp $(addprefix src/, $(SRC)) ./
	mv $(SRC) $(NAME)
	chmod +x $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re