/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:24:01 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/01 17:22:08 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		sizetotal;
	char	*res;
	int		i;
	int		j;

	i = 0;
	if (!s1 || !s2)
		return (free(s1), NULL);
	sizetotal = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	res = malloc(sizeof(char) * (sizetotal + 1));
	if (!res)
		return (free(s1), NULL);
	while (s1[i] != 0)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
		res[i++] = s2[j++];
	res[sizetotal] = '\0';
	return (free(s1), res);
}

void	*ft_memset_gnl(void *ptr, int value, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)ptr;
	while (i < len)
	{
		*str = value;
		str++;
		i++;
	}
	return (ptr);
}

int	ft_strchr_gnl(char *s, int c, int d)
{
	int	len;

	len = 0;
	while (s[len] != 0)
	{
		if (s[len] == (char)c)
			return (len);
		len++;
	}
	if ((char)c == s[len])
		return (len);
	len = 0;
	while (s[len] != 0)
	{
		if (s[len] == (char)d)
			return (len);
		len++;
	}
	if ((char)d == s[len])
		return (len);
	return (-1);
}

int	ft_strlen_gnl(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strncpy_gnl(char *dest, char *src, int n)
{
	int	i;

	dest = malloc(sizeof(char) * (n + 1));
	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
