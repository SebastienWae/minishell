USER = $(shell whoami)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS = -I../include -I../libft -I/goinfre/$(USER)/.brew/include
LDFLAGS = -L../libft -L/goinfre/$(USER)/.brew/lib -lft -lcmocka

tokenizer.test: tokenizer.test.o tokenizer.o strings.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 
	./$@

tokenizer.o: ../src/tokenizer.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ./$@

strings.o: ../src/strings.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ./$@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ./$@
