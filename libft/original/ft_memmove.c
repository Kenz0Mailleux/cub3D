/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:33:04 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/01 17:21:26 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dest_ptr;
	unsigned char		*src_ptr;

	i = 1;
	dest_ptr = (unsigned char *)dst;
	src_ptr = (unsigned char *)src;
	if (dest_ptr == NULL && src_ptr == NULL)
		return (NULL);
	if (src_ptr < dest_ptr)
	{
		while (i <= len)
		{
			dest_ptr[len - i] = src_ptr[len - i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			*(dest_ptr++) = *(src_ptr++);
	}
	return (dst);
}
