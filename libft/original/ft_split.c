/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmailleu <kmailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:31:33 by kmailleu          #+#    #+#             */
/*   Updated: 2023/12/06 16:56:05 by kmailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_string(char *s, char c)
{
	int	len_tot;
	int	i;

	len_tot = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			len_tot++;
		i++;
	}
	return (len_tot);
}

char	*word_malloc(char *s, char c)
{
	int		len_word;
	int		len;
	char	*word;

	len_word = 0;
	len = 0;
	while (s[len_word] != '\0' && s[len_word] != c)
		len_word++;
	word = malloc(sizeof(char) * (len_word + 1));
	if (word == NULL)
		return (NULL);
	while (len < len_word)
	{
		word[len] = s[len];
		len++;
	}
	word[len_word] = '\0';
	return (word);
}

char	**safe_free(char **strings, int j)
{
	while (j >= 0)
		free(strings[j--]);
	free(strings);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	int		count[2];
	char	**strings;

	count[0] = 0;
	count[1] = 0;
	if (str == NULL)
		return (NULL);
	strings = malloc(sizeof(char *) * (count_string((char *)str, c) + 1));
	if (strings == NULL)
		return (NULL);
	while (str[count[0]])
	{
		if (str[count[0]] != c)
		{
			strings[count[1]] = word_malloc((char *)(&str[count[0]]), c);
			if (strings[count[1]++] == NULL)
				return (safe_free(strings, --count[1]));
			while (str[count[0]] && str[count[0]] != c)
				count[0]++;
		}
		else
			count[0]++;
	}
	strings[count[1]] = NULL;
	return (strings);
}
