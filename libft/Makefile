LIBC =	original/ft_isalpha.c \
		original/ft_isdigit.c \
		original/ft_isalnum.c \
		original/ft_isascii.c \
		original/ft_isprint.c \
		original/ft_strlen.c \
		original/ft_strlcat.c \
		original/ft_strlcpy.c \
		original/ft_tolower.c \
		original/ft_toupper.c \
		original/ft_memset.c \
		original/ft_strdup.c \
		original/ft_bzero.c \
		original/ft_memcpy.c \
		original/ft_calloc.c \
		original/ft_putchar_fd.c \
		original/ft_putstr_fd.c \
		original/ft_putendl_fd.c \
		original/ft_putnbr_fd.c \
		original/ft_itoa.c \
		original/ft_strmapi.c \
		original/ft_substr.c \
		original/ft_strchr.c \
		original/ft_memmove.c \
		original/ft_atoi.c \
		original/ft_strjoin.c \
		original/ft_strrchr.c \
		original/ft_strncmp.c \
		original/ft_memchr.c \
		original/ft_strnstr.c \
		original/ft_memcmp.c \
		original/ft_strtrim.c \
		original/ft_striteri.c \
		original/ft_split.c \
		original/ft_lstnew_bonus.c \
		original/ft_lstadd_front_bonus.c \
		original/ft_lstsize_bonus.c \
		original/ft_lstlast_bonus.c \
		original/ft_lstadd_back_bonus.c \
		original/ft_lstdelone_bonus.c \
		original/ft_lstclear_bonus.c \
		original/ft_lstiter_bonus.c \
		original/ft_lstmap_bonus.c \
		printf/char_cvrt.c \
		printf/ft_printf.c \
		printf/hex_cvrt.c \
		printf/nbr_cvrt.c \
		printf/ptr_cvrt.c \
		printf/utils.c \
		gnl/get_next_line_utils.c \
		gnl/get_next_line.c \

SRCS = ${LIBC}

OBJS = ${SRCS:.c=.o}

NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: ${NAME}

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@ar -rsc ${NAME} ${OBJS}

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
