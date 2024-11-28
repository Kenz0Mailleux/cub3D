/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:46:11 by kmailleu          #+#    #+#             */
/*   Updated: 2023/11/24 17:06:35 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *scr, size_t size)
{
	size_t				i;
	unsigned char		*dest_ptr;
	unsigned char		*src_ptr;

	i = 0;
	dest_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)scr;
	if (dest_ptr == NULL && src_ptr == NULL)
		return (dst);
	while (i < size)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}
