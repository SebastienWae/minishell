CC = gcc
CFLAGS = -Wall -Wextra -g3 -fsanitize=address
CPPFLAGS = -I../include -I../libft -I/goinfre/$(USER)/.brew/include -I/goinfre/$(USER)/.brew/opt/readline/include
LDFLAGS = -L../libft -L/goinfre/$(USER)/.brew/lib -lft -lcmocka -L/goinfre/$(USER)/.brew/opt/readline/lib -lreadline -lft

OBJS = $(filter-out %main.o,$(shell find ../debug -name '*.o'))

minishell:
	MAKE_DEBUG=1 $(MAKE) -C ../ re

tokenizer.test: tokenizer.test.o minishell
	$(CC) $(CFLAGS) $(call OBJS) tokenizer.test.o $(LDFLAGS) -o $@ 

parser.test: parser.test.o minishell
	$(CC) $(CFLAGS) $(call OBJS) parser.test.o $(LDFLAGS) -o $@ 

expand.test: expand.test.o minishell
	$(CC) $(CFLAGS) $(call OBJS) expand.test.o $(LDFLAGS) -o $@ 
