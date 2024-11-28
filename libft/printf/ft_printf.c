/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:58:33 by kenzo             #+#    #+#             */
/*   Updated: 2024/02/26 17:04:57 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert_exec(char type, va_list args)
{
	if (type == 'c')
		return (from_char(va_arg(args, int)));
	else if (type == 's')
		return (from_str(va_arg(args, char *)));
	else if (type == 'p')
		return (from_ptr(va_arg(args, unsigned long long)));
	else if (type == 'd' || type == 'i')
		return (from_int(va_arg(args, int)));
	else if (type == 'u')
		return (from_uint(va_arg(args, unsigned int)));
	else if (type == 'x' || type == 'X')
		return (from_x_x(va_arg(args, unsigned int), type));
	else if (type == '%')
	{
		if (ft_putchar('%') == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *text, ...)
{
	int		i;
	int		size;
	int		return_value;
	va_list	args;

	i = -1;
	size = 0;
	va_start(args, text);
	if (text == NULL)
		return (0);
	while (text[++i])
	{
		if (text[i] == '%')
		{
			i++;
			return_value = convert_exec(text[i], args);
		}
		else
			return_value = from_char(text[i]);
		if (return_value == -1)
			return (-1);
		size += return_value;
	}
	va_end(args);
	return (size);
}
