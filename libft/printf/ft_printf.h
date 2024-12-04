/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:38:12 by kenzo             #+#    #+#             */
/*   Updated: 2024/08/24 21:55:28 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../original/libft.h"

int		ft_printf(const char *format, ...);
int		from_char(int c);
int		from_str(char *str);
int		from_ptr(unsigned long long nbr);
int		from_int(int nbr);
int		from_uint(unsigned int nbr);
int		from_x_x(unsigned int nbr, char format);
char	*to_hexa(unsigned long long nbr, char *base);
int		hex_len(unsigned long long nbr);

// utils
int		ft_putstr(char *str);
int		ft_putchar(char str);
void	reverse_string(char *str);

#endif