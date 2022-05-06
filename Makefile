# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seb <seb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/06 12:56:59 by seb              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RM = rm -f
MKDIR = mkdir -p

LIBFT = libft

ifdef MAKE_DEBUG
OUT_DIR = debug
NAME := $(OUT_DIR)$(NAME)
CFLAGS = -g3 -fsanitize=address
else
OUT_DIR = out
endif
DIRS = $(OUT_DIR)/src $(OUT_DIR)/src/tokenizer $(OUT_DIR)/src/tokenizer/handlers

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude
LDFLAGS = -L$(LIBFT) -lft

SRCS = src/main.c src/strings.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/tokenizer_actions.c \
	src/tokenizer/token.c src/tokenizer/handlers/char_handler.c \
	src/tokenizer/handlers/double_quote_handler.c \
	src/tokenizer/handlers/end_handler.c \
	src/tokenizer/handlers/great_handler.c \
	src/tokenizer/handlers/less_handler.c \
	src/tokenizer/handlers/pipe_handler.c \
	src/tokenizer/handlers/single_quote_handler.c \
	src/tokenizer/handlers/unimplemented_handler.c \
	src/tokenizer/handlers/whitespace_handler.c
OBJS = $(addprefix $(OUT_DIR)/,$(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(DIRS) $(OBJS) $(LIBFT)/libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(OUT_DIR)$@

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -c -o $(OUT_DIR)/$@

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
