/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_cvrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:42:37 by kenzo             #+#    #+#             */
/*   Updated: 2024/02/26 16:11:09 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	from_int(int nbr)
{
	char	*nbr_str;
	int		i;

	i = 0;
	nbr_str = ft_itoa(nbr);
	if (nbr_str == NULL)
		return (-1);
	i = ft_putstr(nbr_str);
	free(nbr_str);
	return (i);
}

static int	get_len_nbr(long int n)
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

static char	*ft_uitoa(unsigned int n)
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
	if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		str[len_nbr - i++ - 1] = ('0' + nb % 10);
		nb /= 10;
	}
	str[len_nbr] = '\0';
	return (str);
}

int	from_uint(unsigned int nbr)
{
	int		len;
	char	*str_nbr;

	len = 0;
	if (nbr == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		len++;
	}
	else
	{
		str_nbr = ft_uitoa(nbr);
		if (str_nbr == NULL)
			return (-1);
		len += from_str(str_nbr);
		free(str_nbr);
	}
	return (len);
}
