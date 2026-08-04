NAME	:= libsbuf.a
SRCS	:= src/sbuf_new.c src/sbuf_grow.c src/sbuf_append.c src/sbuf_guys.c
OBJSDIR := build
OBJS 	:= $(patsubst src/%.c,$(OBJSDIR)/%.o,$(SRCS))
HEADERS := include/sbuf/sbuf.h include/sbuf/sbuf_internal.h
TST_SRC := test/test_sbuf.c
TST_FLG := $(shell pkg-config --cflags --libs criterion)
TST_BIN := build/test

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
INCLUDE := -I include
AR 		:= ar rcs
RM 		:= rm -rf




all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJSDIR)/%.o: src/%.c $(HEADER) | $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJSDIR):
	mkdir -p $(OBJSDIR)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) $(INCLUDE) $(TST_SRC) $(TST_FLG) $(NAME) -o $(TST_BIN)
	$(TST_BIN)

.PHONY: all clean fclean re test
