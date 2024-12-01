/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:00:55 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/01 17:21:26 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (needle[len2] == '\0')
		return ((char *)haystack);
	while (haystack[len1] != '\0')
	{
		while (haystack[len1 + len2] == needle[len2] && haystack[len1 + len2]
			!= '\0' && (len1 + len2) < len)
			len2++;
		if (needle[len2] == '\0')
			return ((char *)(haystack + len1));
		len1++;
		len2 = 0;
	}
	return (0);
}
