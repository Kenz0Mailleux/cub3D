/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:15:11 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/01 17:21:26 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	len;
	size_t	res;

	len = 0;
	res = 0;
	while (src[res])
	{
		++res;
	}
	if (size < 1)
	{
		return (res);
	}
	while (src[len] && len < size - 1)
	{
		dest[len] = src[len];
		++len;
	}
	dest[len] = '\0';
	return (res);
}
