/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:22:06 by kmailleu          #+#    #+#             */
/*   Updated: 2023/11/24 17:09:58 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = 0;
	while ((s1[len] != '\0' || s2[len] != '\0') && len < n)
	{
		if ((unsigned char)(s1[len]) != ((unsigned char)(s2[len])))
			return ((unsigned char)(s1[len]) - (unsigned char)(s2[len]));
		len++;
	}
	return (0);
}
