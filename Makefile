# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobin <jrobin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/11 19:28:47 by jrobin            #+#    #+#              #
#    Updated: 2018/04/29 02:19:25 by jrobin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in

NAME_LIB =	libft.a
PATH_LIB =	libft/
LIB =		$(PATH_LIB)$(NAME_LIB)

PATH_INC =	includes/

CC =		gcc
FLAGS =		-Wall -Wextra -Werror

DIR_SRC =	sources/
DIR_OBJ =	obj/

SRC_BASE=	main.c \
		  	collect_parse.c \
		  	new_room.c \
			error.c \
		  	tubes.c \
		  	pathfinding.c \
		  	pathfinding_utils.c \
		 	print_soluce.c \
		  	moving_ants.c \
		  	free.c


OBJS=		$(addprefix $(DIR_OBJ), $(SRC_BASE:.c=.o))

################################################################################

$(DIR_OBJ)%.o: $(DIR_SRC)%.c Makefile
	@$(CC) $(FLAGS) -I $(PATH_INC) -I $(PATH_LIB)$(PATH_INC) -MMD -c $< -o $@

################################################################################

all: $(LIB)
	@make -j $(NAME)

$(LIB):
	@make -C $(PATH_LIB)

$(NAME): $(LIB) $(DIR_OBJ) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(PATH_LIB)$(NAME_LIB) -o $(NAME)
	@echo "\033[32m$(NAME) ok\033[0m"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(dir $(OBJS))

clean:
	@make clean -C $(PATH_LIB)
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -f $(LIB)
	@rm -f $(NAME)

re: fclean all

DEBUG:
	@echo $(OBJS)

.PHONY: all clean fclean re DEBUG LIB libft

-include $(OBJS:.o=.d)
