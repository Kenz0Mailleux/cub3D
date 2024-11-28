/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:48:20 by kmailleu          #+#    #+#             */
/*   Updated: 2023/11/14 16:38:19 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len_nbr(long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			i;
	int			len_nbr;
	char		*str;
	long int	nb;

	nb = n;
	len_nbr = get_len_nbr(nb);
	i = 0;
	str = malloc((len_nbr + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nb < 0)
	{
		str[i] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[i] = '0';
	while (nb > 0)
	{
		str[len_nbr - i++ - 1] = ('0' + nb % 10);
		nb /= 10;
	}
	str[len_nbr] = '\0';
	return (str);
}
