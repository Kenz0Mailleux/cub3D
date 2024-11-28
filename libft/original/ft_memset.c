/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:16:35 by kmailleu          #+#    #+#             */
/*   Updated: 2023/11/24 17:12:40 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
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
