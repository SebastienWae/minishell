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

RM = rm -f
MKDIR = mkdir

LIBFT = libft

SRC_DIR = ./src/

ifdef MAKE_DEBUG
OUT_DIR = ./debug/
NAME := $(OUT_DIR)$(NAME)
DIRS = $(OUT_DIR)
CFLAGS = -g3 -fsanitize=address
else
OUT_DIR = ./
endif

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude -I/goinfre/$(USER)/.brew/opt/readline/include
LDFLAGS = -L$(LIBFT) -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline -lft

SRCS = main.c \
		init.c close_functions.c \
		fd_manager.c \
		sys_call.c \
		signal_handler.c \
		builtin_functions_1.c builtin_functions_2.c errors.c \
		builtin_functions_utils.c builtin_functions_utils2.c \
		ft_better_split.c ft_strcmp.c \
		main_pipex.c utils_pipex.c pipex.c

OBJS = $(addprefix $(OUT_DIR),$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(DIRS) $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OUT_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $@

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT) bonus

$(DIRS):
	$(MKDIR) "$@"

check: CFLAGS = -fanalyzer
check: re

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

compile_commands:
	compiledb -f make re

.PHONY: all clean fclean re $(LIBFT) compile_commands
