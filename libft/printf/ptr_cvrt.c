/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_cvrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:08:48 by kmailleu          #+#    #+#             */
/*   Updated: 2024/02/26 16:42:52 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	from_ptr(unsigned long long nbr)
{
	int		len;
	char	*nbr_str;

	len = 0;
	if (write(1, "0x", 2) == -1)
		return (-1);
	len += 2;
	nbr_str = to_hexa(nbr, "0123456789abcdef");
	if (nbr_str == NULL)
		return (-1);
	if (nbr == 0)
	{
		ft_putchar('0');
		len += 1;
	}
	else
		len += ft_putstr(nbr_str);
	free(nbr_str);
	return (len);
}
