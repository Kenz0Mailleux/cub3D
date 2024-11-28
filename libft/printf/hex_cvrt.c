/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_cvrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:44:12 by kmailleu          #+#    #+#             */
/*   Updated: 2024/02/26 16:58:57 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_len(unsigned long long nbr)
{
	int	len;

	len = 0;
	while (nbr > 16)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}

char	*to_hexa(unsigned long long nbr, char *base)
{
	int		i;
	char	*nbr_hex;
	int		rest;

	i = 0;
	nbr_hex = malloc(sizeof(char *) * (hex_len(nbr) + 1));
	if (nbr_hex == NULL)
		return (NULL);
	while (nbr != 0)
	{
		rest = nbr % 16;
		nbr_hex[i++] = base[rest];
		nbr /= 16;
	}
	nbr_hex[i] = '\0';
	reverse_string(nbr_hex);
	return (nbr_hex);
}

int	from_x_x(unsigned int nbr, char format)
{
	int		len;
	char	*nbr_str;

	len = 0;
	nbr_str = NULL;
	if (nbr == 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		len++;
	}
	if (format == 'x')
		nbr_str = to_hexa(nbr, "0123456789abcdef");
	else if (format == 'X')
		nbr_str = to_hexa(nbr, "0123456789ABCDEF");
	if (nbr_str == NULL)
		return (-1);
	len += ft_putstr(nbr_str);
	return (free(nbr_str), len);
}
