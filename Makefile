# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seb <seb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/07 13:59:16 by seb              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RM = rm -f
MKDIR = mkdir -p

LIBFT = libft

ifdef MAKE_DEBUG
OUT_DIR = debug
CFLAGS = -g3 -fsanitize=address
NAME = minishell_debug
else
OUT_DIR = out
endif
DIRS = $(OUT_DIR)/src $(OUT_DIR)/src/tokenizer $(OUT_DIR)/src/tokenizer/handlers

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude
LDFLAGS = -L$(LIBFT) -lft

SRCS = src/main.c src/strings.c src/debug.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/tokenizer_actions.c \
	src/tokenizer/handlers/char_handler.c \
	src/tokenizer/handlers/double_quote_handler.c \
	src/tokenizer/handlers/end_handler.c \
	src/tokenizer/handlers/great_handler.c \
	src/tokenizer/handlers/less_handler.c \
	src/tokenizer/handlers/pipe_handler.c \
	src/tokenizer/handlers/single_quote_handler.c \
	src/tokenizer/handlers/whitespace_handler.c
OBJS = $(addprefix $(OUT_DIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(DIRS) $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
