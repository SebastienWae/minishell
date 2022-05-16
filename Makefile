# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 13:49:18 by swaegene          #+#    #+#              #
#    Updated: 2022/05/16 17:17:53 by jeulliot         ###   ########.fr        #
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
NAME := $(NAME)_debug
else
OUT_DIR = out
endif

CC = gcc
CFLAGS += -Wall -Wextra -Werror
CPPFLAGS = -I$(LIBFT) -Iinclude -I/goinfre/$(USER)/.brew/opt/readline/include
LDFLAGS = -L$(LIBFT) -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline -lft

SRCS = main.c debug.c \
	utils/ft_better_split.c \
	utils/get_next_line.c \
	utils/get_next_line_utils.c \
	utils/strings.c \
	sys/calls.c \
	sys/cmds.c \
	sys/exec.c \
	sys/fd.c \
	sys/fd_utils.c \
	sys/signals.c \
	functions/cd.c \
	functions/echo.c \
	functions/env.c \
	functions/env_utils.c \
	functions/exit.c \
	functions/pwd.c \
	tokenizer/tokenizer.c \
	tokenizer/tokenizer_actions.c \
	tokenizer/handlers/char_handler.c \
	tokenizer/handlers/double_quote_handler.c \
	tokenizer/handlers/end_handler.c \
	tokenizer/handlers/great_handler.c \
	tokenizer/handlers/less_handler.c \
	tokenizer/handlers/pipe_handler.c \
	tokenizer/handlers/single_quote_handler.c \
	tokenizer/handlers/whitespace_handler.c \
	parser/parser.c \
	parser/parser_cmds.c \
	parser/parser_actions.c \
	parser/parser_redirections.c \
	parser/handlers/heredoc_handler.c \
	parser/handlers/pipe_handler.c \
	parser/handlers/redirection_append_handler.c \
	parser/handlers/redirection_in_handler.c \
	parser/handlers/redirection_out_handler.c \
	parser/handlers/word_handler.c \
	expand/expand.c \
	expand/expand_handlers.c \
	expand/expand_actions.c
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
	$(RM) tmp/fd_tmp

re: fclean all

compile_commands: $(LIBFT)/libft.a
	bear -- make re

.PHONY: all clean fclean re $(LIBFT) compile_commands
