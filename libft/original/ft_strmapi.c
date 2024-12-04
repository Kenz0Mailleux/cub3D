/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:08:26 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/01 17:21:26 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	int				len;
	unsigned int	i;

	if (s == 0 || f == NULL)
		return (0);
	i = 0;
	len = ft_strlen(s);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
