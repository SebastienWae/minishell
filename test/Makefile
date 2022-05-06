CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS = -I../include -I../libft -I/goinfre/$(USER)/.brew/include
LDFLAGS = -L../libft -L/goinfre/$(USER)/.brew/lib -lft -lcmocka

OBJS = $(shell find ../debug -name '*.o')
OBJS := $(filter-out %main.o,$(OBJS))

minishell:
	MAKE_DEBUG=1 $(MAKE) -C ../ re

tokenizer.test: tokenizer.test.o minishell
	$(CC) $(CFLAGS) $(OBJS) tokenizer.test.o $(LDFLAGS) -o $@ 
