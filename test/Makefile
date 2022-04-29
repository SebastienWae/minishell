CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS = -I../include -I../libft
LDFLAGS = -L../libft -lft -lcmocka

tokenizer.test: tokenizer.test.o tokenizer.o strings.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ 
	./$@

tokenizer.o: ../src/tokenizer.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ./$@

strings.o: ../src/strings.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ./$@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ./$@
