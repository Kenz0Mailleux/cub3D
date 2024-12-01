/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_cvrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:09:36 by kmailleu          #+#    #+#             */
/*   Updated: 2024/12/01 17:23:13 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
