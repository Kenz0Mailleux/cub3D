/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_cvrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:09:36 by kmailleu          #+#    #+#             */
/*   Updated: 2024/02/26 16:34:03 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	from_char(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	from_str(char *str)
{
	if (str == NULL)
		return (ft_putstr(("(null)")));
	return (ft_putstr(str));
}
