# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/11 19:28:47 by jrobin            #+#    #+#              #
#    Updated: 2018/04/06 02:02:55 by jrobin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=	lem-in

NAME_LIB=	libft.a
PATH_LIB=	libft/
LIB =		$(PATH_LIB)$(NAME_LIB)

PATH_INC=	includes/

CC=			gcc
FLAGS=		-Wall -Wextra -Werror -g -fsanitize=address

DIR_SRC:=	sources/
DIR_OBJ:=	obj/

SRC_BASE= main.c \
		  collect_parse.c \
		  new_room.c \
		  error.c \
		  ants.c \
		  tubes.c \
		  pathfinding.c \

OBJS=		$(addprefix $(DIR_OBJ), $(SRC_BASE:.c=.o))

all: 
	make -C $(PATH_LIB)
	@make -j $(NAME)

$(LIB):
	@make -C $(PATH_LIB)

$(NAME): $(LIB) $(DIR_OBJ) $(OBJS) Makefile
	$(CC) $(FLAGS) $(OBJS) $(PATH_LIB)$(NAME_LIB) -o $(NAME)
	@echo "\033[32mlem-in ok\033[0m"

DEBUG: 
	@echo $(OBJS)


$(DIR_OBJ):
		@mkdir -p $(DIR_OBJ)
		@mkdir -p $(dir $(OBJS))

$(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@$(CC) $(FLAGS) -I $(PATH_INC) -I $(PATH_LIB)$(PATH_INC) -MMD -c $< -o $@  

clean:
	make clean -C $(PATH_LIB)
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(LIB)
	@rm -f $(NAME)

re: fclean all

.PHONY :	all clean fclean re DEBUG LIB libft
