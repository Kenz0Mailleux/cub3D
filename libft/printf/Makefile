NAME = libftprintf.a
LIBFTNAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFTDIR = ../original

SRCS = ft_printf.c \
       char_cvrt.c \
       hex_cvrt.c \
       nbr_cvrt.c \
       ptr_cvrt.c \
       utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): makelibft $(OBJS)
	@ar rcs $(NAME) $(OBJS)

makelibft:
	@$(MAKE) -C $(LIBFTDIR) > /dev/null 2>&1
	@cp $(LIBFTDIR)/$(LIBFTNAME) .
	@mv $(LIBFTNAME) $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFTDIR) clean > /dev/null 2>&1

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: all makelibft clean fclean re
