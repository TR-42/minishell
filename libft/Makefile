# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 06:23:32 by kfujita           #+#    #+#              #
#    Updated: 2023/03/02 11:28:13 by kfujita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS_IS	= \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_islower.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_isupper.c \

SRCS_LST	= \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \

SRCS_MATH	= \
	can_add.c \
	can_mul.c \
	ft_max.c \
	ft_min.c \

SRCS_MEM	= \
	ft_bzero.c \
	ft_calloc.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_swap.c \

SRCS_PRINTF	= \
	check_no_opt_str.c \
	ft_printf.c \
	is_valid_conv_char.c \
	is_valid_flag_char.c \
	parse_format.c \
	parse_opt_c_str.c \
	parse_opt_flags.c \
	parse_opt_num.c \
	parse_opt_ptr.c \
	parse_opt.c \
	print_all.c \

SRCS_PUT	= \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \

SRCS_SORT	= \
	ft_qsort.c

SRCS_STRING	= \
	ft_atoi_strict.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strndup.c \
	ft_strnlen.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtol.c \
	ft_strtrim.c \
	ft_substr.c \
	get_numstr_base.c \

SRCS_TO	= \
	ft_tolower.c \
	ft_toupper.c \

SRCS_VECT	= \
	vect_append_range.c \
	vect_at.c \
	vect_dispose.c \
	vect_init.c \
	vect_push_back.c \
	vect_remove.c \
	vect_reserve.c \
	vect_set.c \

SRCS_GNL	= \
	get_next_line.c \

SRCS	= \
	$(SRCS_IS)\
	$(SRCS_LST)\
	$(SRCS_MATH)\
	$(SRCS_MEM)\
	$(SRCS_PRINTF)\
	$(SRCS_PUT)\
	$(SRCS_SORT)\
	$(SRCS_STRING)\
	$(SRCS_TO)\
	$(SRCS_VECT)\
	$(SRCS_GNL)\

FT_IS_DIR	=	./ft_is
SRCS04_DIR	=	./ft_lst
FT_MATH_DIR	=	./ft_math
FT_MEM_DIR	=	./ft_mem
PRINTF_DIR	=	./ft_printf
FT_PUT_DIR	=	./ft_put
SORT_DIR	=	./ft_sort
STR_DIR		=	./ft_string
FT_TO_DIR	=	./ft_to
FT_VECT_DIR	=	./ft_vect
GNL_DIR		=	./gnl

OBJ_DIR	=	./obj
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.d))

VPATH	=	\
	$(FT_IS_DIR)\
	:$(SRCS04_DIR)\
	:$(FT_MATH_DIR)\
	:$(FT_MEM_DIR)\
	:$(PRINTF_DIR)\
	:$(FT_PUT_DIR)\
	:$(SORT_DIR)\
	:$(STR_DIR)\
	:$(FT_TO_DIR)\
	:$(FT_VECT_DIR)\
	:$(GNL_DIR)\

CFLAGS	=	-Wall -Wextra -Werror -MMD

CC		=	cc

MAKE_OBJ_CMD	=	$(CC) $(CFLAGS) -c -o $@ $<

all:	$(NAME)

$(NAME):	$(OBJS)
	ar r $@ $^

$(OBJ_DIR)/%.o:	%.c
	@mkdir -p $(OBJ_DIR)
	$(MAKE_OBJ_CMD)

bonus:	$(NAME)

clean:
	rm -f $(OBJS) $(DEPS)
	rm -d $(OBJ_DIR) || exit 0

fclean:	clean
	rm -f $(NAME)

re:	fclean all

-include $(DEPS)

.PHONY:	clean
