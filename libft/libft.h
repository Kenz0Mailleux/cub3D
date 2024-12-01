/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:47:58 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/01 17:27:03 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include <stdint.h>

/* printf include */
# include <stdarg.h>
# include <limits.h>

/* libc functions */
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *destination, const void *source, size_t size);
void	*ft_memccpy(void *destination, const void *source, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *string, int sc);
char	*ft_strrchr(const char *string, int sc);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

/* additional functions */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/* bonus functions */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}						t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* gnl functions */
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strchr_gnl(char *string, int c, int d);
int		ft_strlen_gnl(char *str);
char	*ft_strncpy_gnl(char *dest, char *src, int n);
void	*ft_memset_gnl(void *ptr, int value, size_t len);

/* printf functions */
int		ft_printf(const char *format, ...);
int		from_char(int c);
int		from_str(char *str);
int		from_ptr(unsigned long long nbr);
int		from_int(int nbr);
int		from_uint(unsigned int nbr);
int		from_x_x(unsigned int nbr, char format);
char	*to_hexa(unsigned long long nbr, char *base);
int		hex_len(unsigned long long nbr);

// utils
int		ft_putstr(char *str);
int		ft_putchar(char str);
void	reverse_string(char *str);

#endif