NAME = lbftgnl.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCDIR = .

SRCS = get_next_line.c \
       get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "Library created: $(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled: $<"

clean:
	@rm -f $(OBJS)
	@echo "Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned library"

re: fclean all

.PHONY: all clean fclean re
