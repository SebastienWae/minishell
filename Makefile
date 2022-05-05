# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seb <seb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/05 11:01:31 by seb              ###   ########.fr        #
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
CPPFLAGS = -I$(LIBFT) -Iinclude
LDFLAGS = -L$(LIBFT) -lft

SRCS = main.c strings.c token.c tokens.c tokenizer.c tokenizer_states.c \
	tokenizer_operators.c
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

compile_commands: $(LIBFT)/libft.a
	bear -- make re	

.PHONY: all clean fclean re $(LIBFT) compile_commands
