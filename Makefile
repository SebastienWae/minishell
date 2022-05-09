# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/04/28 15:45:35 by swaegene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RM = rm -rf
MKDIR = mkdir -p

LIBFT = libft

ifdef MAKE_DEBUG
OUT_DIR = debug
CFLAGS = -g3 -fsanitize=address
NAME = minishell_debug
else
OUT_DIR = out
endif


CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude -I/goinfre/$(USER)/.brew/opt/readline/include
LDFLAGS = -L$(LIBFT) -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline -lft

SRCS = src/main.c src/init.c \
		src/functions/builtin_functions_1.c src/functions/builtin_functions_2.c \
		src/functions/builtin_functions_utils.c \
		src/functions/builtin_functions_utils2.c \
		src/functions/pipe.c src/functions/sys_call.c \
		src/gnl/get_next_line.c src/gnl/get_next_line_utils.c \
		src/strings_utils/ft_better_split.c src/strings_utils/ft_strcmp.c \
		src/closing_utils.c src/errors.c src/fd_manager.c src/signal_handler.c

		

OBJS = $(addprefix $(OUT_DIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OUT_DIR)/%.o: %.c
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) bonus


check: CFLAGS = -fanalyzer
check: re

clean: 
	$(RM) $(OUT_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

compile_commands: $(LIBFT)/libft.a
	bear -- make re

.PHONY: all clean fclean re $(LIBFT) compile_commands