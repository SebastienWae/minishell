# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seb <seb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/09 13:15:25 by swaegene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RM = rm -rf
MKDIR = mkdir -p

LIBFT = libft
SRC_DIR = src

ifdef MAKE_DEBUG
OUT_DIR = debug
CFLAGS = -g3 -fsanitize=address
NAME += _debug
else
OUT_DIR = out
endif

CC = clang
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude -I/goinfre/$(USER)/.brew/opt/readline/include
LDFLAGS = -L$(LIBFT) -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline -lft

SRCS = main.c strings.c debug.c \
	tokenizer/tokenizer.c \
	tokenizer/tokenizer_actions.c \
	tokenizer/handlers/char_handler.c \
	tokenizer/handlers/double_quote_handler.c \
	tokenizer/handlers/end_handler.c \
	tokenizer/handlers/great_handler.c \
	tokenizer/handlers/less_handler.c \
	tokenizer/handlers/pipe_handler.c \
	tokenizer/handlers/single_quote_handler.c \
	tokenizer/handlers/whitespace_handler.c
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
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
