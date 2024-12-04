/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:36:16 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/01 17:27:26 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		ft_strchr_gnl(char *string, int c, int d);
int		ft_strlen_gnl(char *str);
char	*ft_strncpy_gnl(char *dest, char *src, int n);
void	*ft_memset_gnl(void *ptr, int value, size_t len);

#endif