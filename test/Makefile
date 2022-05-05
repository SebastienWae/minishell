USER = $(shell whoami)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS = -I../include -I../libft -I/goinfre/$(USER)/.brew/include
LDFLAGS = -L../libft -L/goinfre/$(USER)/.brew/lib -lft -lcmocka

tokenizer.test: tokenizer.test.o tokenizer.c strings.c tokenizer_operators.c tokenizer_states.c token.c tokens.c
	$(CC) $(CFLAGS) $(^:%.c=%.o) $(LDFLAGS) -o $@ 
	./$@

%.c:
	$(CC) $(CFLAGS) $(CPPFLAGS) ../src/$@ -c -o $(@:%.c=%.o)
