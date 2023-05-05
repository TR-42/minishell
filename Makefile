# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:44:27 by kfujita           #+#    #+#              #
#    Updated: 2023/05/05 23:27:15 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS_MAIN	= \
	main.c \

SRCS_NOMAIN	= \

HEADERS_DIR		=	./headers

SRCS_BASE_DIR	=	./srcs
SRCS_MAIN_DIR	=	$(SRCS_BASE_DIR)

OBJ_DIR	=	./obj
OBJS_NOMAIN	=	$(addprefix $(OBJ_DIR)/, $(SRCS_NOMAIN:.c=.o))
OBJS	=	$(OBJS_NOMAIN) $(addprefix $(OBJ_DIR)/, $(SRCS_MAIN:.c=.o))
DEPS	=	$(addprefix $(OBJ_DIR)/, $(OBJS:.o=.d))

VPATH	=	\
	$(SRCS_MAIN_DIR)\

LIBFT_DIR	=	./libft
LIBFT	=	$(LIBFT_DIR)/libft.a
LIBFT_MAKE	=	make -C $(LIBFT_DIR)

CFLAGS	=	-Wall -Wextra -Werror -MMD -MP
INCLUDES	=	-I $(HEADERS_DIR) -I $(LIBFT_DIR)

CC		=	cc

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(OBJ_DIR)/%.o:	%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(LIBFT):
	$(LIBFT_MAKE)

bonus:	$(NAME)

clean_local:
	rm -f $(OBJS) $(DEPS)
	rm -d $(OBJ_DIR) || exit 0

fclean_local: clean_local
	rm -f $(NAME)

clean: clean_local
	$(LIBFT_MAKE) clean

fclean:	fclean_local
	$(LIBFT_MAKE) fclean

re:	fclean all

norm:
	norminette $(HEADERS_DIR) $(SRC_DIR)

-include $(DEPS)

.PHONY:	clean_local bonus norm
