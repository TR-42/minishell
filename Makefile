# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:44:27 by kfujita           #+#    #+#              #
#    Updated: 2023/05/17 23:25:50 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS_MAIN	= \
	main.c \

SRCS_CHILDS	=\
	_get_argc.c\
	_one_elem_count.c\
	build_cmd.c\
	childs_dispose.c\
	childs.c\
	env_util.c\
	exec_cmd.c\
	filectrl_tools.c\
	init_ch_proc_info_arr.c\

SRCS_SERIALIZER	= \
	_serializer_dquote.c \
	_serializer_pipe_red.c \
	_serializer_squote.c \
	_serializer_var.c \
	dispose_t_cmd.c \
	is_cetyp.c \
	serializer.c \

SRCS_VALIDATOR =\
	is_valid_cmd.c\
	is_valid_input.c\

SRCS_NOMAIN	= \
	$(SRCS_CHILDS)\
	$(SRCS_SERIALIZER)\
	$(SRCS_VALIDATOR)\

HEADERS_DIR		=	./headers

SRCS_BASE_DIR	=	./srcs
SRCS_MAIN_DIR	=	$(SRCS_BASE_DIR)
SRCS_CHILDS_DIR	=	$(SRCS_BASE_DIR)/childs
SRCS_SERIALIZER_DIR	=	$(SRCS_BASE_DIR)/serializer
SRCS_VALIDATOR_DIR	=	$(SRCS_BASE_DIR)/validator

OBJ_DIR	=	./obj
OBJS_NOMAIN	=	$(addprefix $(OBJ_DIR)/, $(SRCS_NOMAIN:.c=.o))
OBJS	=	$(OBJS_NOMAIN) $(addprefix $(OBJ_DIR)/, $(SRCS_MAIN:.c=.o))
DEPS	=	$(addprefix $(OBJ_DIR)/, $(OBJS:.o=.d))

VPATH	=	\
	$(SRCS_MAIN_DIR)\
	:$(SRCS_CHILDS_DIR)\
	:$(SRCS_SERIALIZER_DIR)\
	:$(SRCS_VALIDATOR_DIR)\

TEST_DIR	=	.tests
TEST_SERIALIZER	=	test_serializer
TEST_BUILD_CMD	=	test_build_cmd

LIBFT_DIR	=	./libft
LIBFT	=	$(LIBFT_DIR)/libft.a
LIBFT_MAKE	=	make -C $(LIBFT_DIR)

override CFLAGS	+=	-Wall -Wextra -Werror -MMD -MP
INCLUDES	=	-I $(HEADERS_DIR) -I $(LIBFT_DIR)

CC		=	cc

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
debug: clean_local
	make CFLAGS='-DDEBUG'

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

	@./$(TEST_DIR)/$(TEST_BUILD_CMD).sh $(OBJ_DIR)/$(TEST_BUILD_CMD)


$(OBJ_DIR)/$(TEST_SERIALIZER): ./$(TEST_DIR)/$(TEST_SERIALIZER).c $(LIBFT) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(OBJ_DIR)/$(TEST_BUILD_CMD): ./$(TEST_DIR)/$(TEST_BUILD_CMD).c $(LIBFT) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
