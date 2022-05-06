USER = $(shell whoami)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS = -I../include -I../libft -I/goinfre/$(USER)/.brew/include
LDFLAGS = -L../libft -L/goinfre/$(USER)/.brew/lib -lft -lcmocka

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

OBJS = $(addprefix $(OUT_DIR),$(SRCS:%.c=%.o))
tokenizer.test: tokenizer.test.o 
	$(CC) $(CFLAGS) $(^:%.c=%.o) $(LDFLAGS) -o $@ 
	./$@

%.c:
	$(CC) $(CFLAGS) $(CPPFLAGS) ../src/$@ -c -o $(@:%.c=%.o)
