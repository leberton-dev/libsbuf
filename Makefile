NAME	:= libsbuf.a
SRCS	:= src/sbuf.c
OBJSDIR := build
OBJS 	:= $(patsubst src/%.c,$(OBJSDIR)/%.o,$(SRCS))
HEADERS := include/sbuf/sbuf.h

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
	$(CC) $(CFLAGS) $(INCLUDE) main.c $(NAME) -o $(OBJSDIR)/test_main
	$(OBJSDIR)/test_main

.PHONY: all clean fclean re test
