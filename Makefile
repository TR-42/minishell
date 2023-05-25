# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 18:44:27 by kfujita           #+#    #+#              #
#    Updated: 2023/05/23 23:51:13 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

SRCS_MAIN	:= \
	main.c \

SRCS_CHILDS	:=\
	_exec_ch_proc_info_arr.c\
	_get_argc.c\
	_one_elem_count.c\
	_redirect.c\
	_parse_exec.c\
	build_cmd.c\
	childs_dispose.c\
	childs.c\
	env_util.c\
	exec_cmd.c\
	filectrl_tools.c\
	init_ch_proc_info_arr.c\

SRCS_HEREDOC :=\
	chk_do_heredoc.c\
	create_tmpfile.c\
	rm_tmpfile.c\

SRCS_SERIALIZER	:= \
	_serializer_dquote.c \
	_serializer_pipe_red.c \
	_serializer_squote.c \
	_serializer_var.c \
	dispose_t_cmd.c \
	is_cetyp.c \
	serializer.c \

SRCS_VALIDATOR :=\
	_validate_input.c\
	is_valid_cmd.c\
	is_valid_input.c\

SRCS_NOMAIN	:= \
	$(addprefix childs/, $(SRCS_CHILDS))\
	$(addprefix heredoc/, $(SRCS_HEREDOC))\
	$(addprefix serializer/, $(SRCS_SERIALIZER))\
	$(addprefix validator/, $(SRCS_VALIDATOR))\

HEADERS_DIR		:=	./headers

SRCS_BASE_DIR	:=	./srcs

OBJ_DIR	:=	./obj
OBJS_NOMAIN	:=	$(addprefix $(OBJ_DIR)/, $(SRCS_NOMAIN:.c=.o))
OBJS	:=	$(OBJS_NOMAIN) $(addprefix $(OBJ_DIR)/, $(SRCS_MAIN:.c=.o))
DEPS	:=	$(addprefix $(OBJ_DIR)/, $(OBJS:.o=.d))

TEST_DIR	:=	.tests
TEST_SERIALIZER	:=	test_serializer
TEST_BUILD_CMD	:=	test_build_cmd

LIBFT_DIR	:=	./libft
LIBFT	:=	$(LIBFT_DIR)/libft.a
LIBFT_MAKE	:=	make -C $(LIBFT_DIR)

override CFLAGS	+=	-Wall -Wextra -Werror -MMD -MP
INCLUDES	:=	-I $(HEADERS_DIR) -I $(LIBFT_DIR)
LIB_LINK	:=	-lreadline

# os switch ref: https://qiita.com/y-vectorfield/items/5e117e090ed38422de6b
OS_TYPE	:= $(shell uname -s)
ifeq ($(OS_TYPE),Darwin)
	GNU_READLINE_DIR := $(shell brew --prefix readline)
	INCLUDES += -I$(GNU_READLINE_DIR)/include
	LIB_LINK += -L$(GNU_READLINE_DIR)/lib
endif

CC		:=	cc

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIB_LINK)
debug: clean_local
	make CFLAGS='-DDEBUG -g -fsanitize=address'

$(OBJ_DIR)/%.o:	$(SRCS_BASE_DIR)/%.c
	@test -d '$(dir $@)' || mkdir -p '$(dir $@)'
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
	norminette $(HEADERS_DIR) $(SRCS_BASE_DIR)

-include $(DEPS)

.PHONY:	clean_local bonus norm

t: test
test:\
	$(OBJ_DIR)/$(TEST_SERIALIZER)\
	$(OBJ_DIR)/$(TEST_BUILD_CMD)\

	@echo '~~~~~~~~~~ TEST ~~~~~~~~~~~~'
	@./$(TEST_DIR)/$(TEST_SERIALIZER).sh $(OBJ_DIR)/$(TEST_SERIALIZER)

	@./$(TEST_DIR)/$(TEST_BUILD_CMD).sh $(OBJ_DIR)/$(TEST_BUILD_CMD)


$(OBJ_DIR)/$(TEST_SERIALIZER): ./$(TEST_DIR)/$(TEST_SERIALIZER).c $(LIBFT) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_LINK) -o $@ $^

$(OBJ_DIR)/$(TEST_BUILD_CMD): ./$(TEST_DIR)/$(TEST_BUILD_CMD).c $(LIBFT) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIB_LINK) -o $@ $^
