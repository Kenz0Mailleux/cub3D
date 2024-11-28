/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:31:27 by kenzo             #+#    #+#             */
/*   Updated: 2023/12/06 16:18:46 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	max_len;

	if (s == NULL)
		return (NULL);
	max_len = len;
	i = 0;
	if (ft_strlen(s) < len)
		max_len = ft_strlen(s);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	str = malloc(sizeof(*s) * (max_len + 1));
	if (str == NULL)
		return (NULL);
	while (s[start + i] != 0 && i < len && start < ft_strlen(s))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
