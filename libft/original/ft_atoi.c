/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:27:46 by kenzo             #+#    #+#             */
/*   Updated: 2024/02/06 17:50:07 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	sign_space(const char *str, int *ptr_len)
{
	int	sign;
	int	len;

	len = 0;
	sign = 1;
	while ((str[len] >= 9 && str[len] <= 13) || str[len] == 32)
		len++;
	if (str[len] && (str[len] == 43 || str[len] == 45))
	{
		if (str[len] == '-')
			sign *= -1;
		len++;
	}
	*ptr_len = len;
	return (sign);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	result;
	int					len;
	int					len_nb;

	result = 0;
	sign = sign_space(str, &len);
	len_nb = len;
	while (str[len] && str[len] == '0')
		len++;
	while (str[len] && str[len] >= 48 && str[len] <= 57)
	{
		result *= 10;
		result += str[len] - '0';
		len++;
		len_nb++;
		if (result > (unsigned)LONG_MAX)
		{
			if (sign > 0)
				return (-1);
			if (sign < 0)
				return (0);
		}
	}
	return ((int)result * sign);
}
