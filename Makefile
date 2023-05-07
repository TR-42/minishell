# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:44:27 by kfujita           #+#    #+#              #
#    Updated: 2023/05/08 00:32:38 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS_MAIN	= \
	main.c \

SRCS_CHILDS	=\
	env_util.c\
	filectrl_tools.c\

SRCS_SERIALIZER	= \
	_serializer_dquote.c \
	_serializer_pipe_red.c \
	_serializer_squote.c \
	_serializer_var.c \
	dispose_t_cmd.c \
	serializer.c \

SRCS_NOMAIN	= \
	$(SRCS_CHILDS)\
	$(SRCS_SERIALIZER)\

HEADERS_DIR		=	./headers

SRCS_BASE_DIR	=	./srcs
SRCS_MAIN_DIR	=	$(SRCS_BASE_DIR)
SRCS_CHILDS_DIR	=	$(SRCS_BASE_DIR)/childs
SRCS_SERIALIZER_DIR	=	$(SRCS_BASE_DIR)/serializer

OBJ_DIR	=	./obj
OBJS_NOMAIN	=	$(addprefix $(OBJ_DIR)/, $(SRCS_NOMAIN:.c=.o))
OBJS	=	$(OBJS_NOMAIN) $(addprefix $(OBJ_DIR)/, $(SRCS_MAIN:.c=.o))
DEPS	=	$(addprefix $(OBJ_DIR)/, $(OBJS:.o=.d))

VPATH	=	\
	$(SRCS_MAIN_DIR)\
	:$(SRCS_CHILDS_DIR)\
	:$(SRCS_SERIALIZER_DIR)\

TEST_DIR	=	.tests
TEST_SERIALIZER	=	test_serializer

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
	rm -rf $(OBJ_DIR)

fclean_local: clean_local
	rm -f $(NAME)

clean: clean_local
	$(LIBFT_MAKE) clean

fclean:	fclean_local
	$(LIBFT_MAKE) fclean

re:	fclean all

norm:
	norminette $(HEADERS_DIR) $(SRCS_MAIN_DIR)

-include $(DEPS)

.PHONY:	clean_local bonus norm

t: test
test:\
	$(OBJ_DIR)/$(TEST_SERIALIZER)\

	@echo '~~~~~~~~~~ TEST ~~~~~~~~~~~~'
	@./$(TEST_DIR)/$(TEST_SERIALIZER).sh $(OBJ_DIR)/$(TEST_SERIALIZER)


$(OBJ_DIR)/$(TEST_SERIALIZER): ./$(TEST_DIR)/$(TEST_SERIALIZER).c $(LIBFT) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
