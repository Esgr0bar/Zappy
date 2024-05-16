##
## EPITECH PROJECT, 2023
## B-YEP-400-PAR-4-1-zappy-jules.gresset
## File description:
## Makefile
##

NAME_GUI = zappy_gui

NAME_SERVER	= zappy_server

NAME_AI = zappy_ai

all:
	$(MAKE) -C ./gui/
	$(MAKE) -C ./server/
	$(MAKE) -C ./ai/
	mv ./gui/$(NAME_GUI) ./
	mv ./server/$(NAME_SERVER) ./
	mv ./ai/$(NAME_AI) ./

debug:
	make debug -C ./gui/
	make debug -C ./server/
	make debug -C ./ai/


gui:
	$(MAKE) -C ./gui/
	mv ./gui/$(NAME_GUI) ./

server:
	$(MAKE) -C ./server/
	mv ./server/$(NAME_SERVER) ./

ai:
	$(MAKE) -C ./ai/
	mv ./ai/$(NAME_AI) ./

clean:
	make clean -C ./gui/
	make clean -C ./server/
	make clean -C ./ai/

fclean: clean
	make fclean -C ./gui/
	make fclean -C ./server/
	make fclean -C ./ai/
	$(RM) $(NAME_GUI)
	$(RM) $(NAME_SERVER)
	$(RM) $(NAME_AI)

re: fclean all

doc:
	doxygen doc/Doxyfile
	open doc/html/index.html

.PHONY: all clean fclean re debug server client doc ai