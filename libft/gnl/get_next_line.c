/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenzo <kenzo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:15:44 by kenzo             #+#    #+#             */
/*   Updated: 2024/12/01 17:18:43 by kenzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*read_line(int fd, char *stock)
{
	char	*line_read;
	char	*line;
	int		i;

	line = NULL;
	if (ft_strchr_gnl(stock, '\n', '\n') > -1)
		return (ft_strncpy_gnl(line, stock, ft_strlen_gnl(stock)));
	line_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line_read)
		return (NULL);
	line = ft_strncpy_gnl(line, stock, ft_strlen_gnl(stock));
	if (line == NULL)
		return (free(line), free(line_read), NULL);
	while (1)
	{
		i = read(fd, line_read, BUFFER_SIZE);
		if (i == -1)
			return (free(line), free(line_read), NULL);
		line_read[i] = '\0';
		line = ft_strjoin_gnl(line, line_read);
		if (line == NULL)
			return (free(line), free(line_read), NULL);
		if (i == 0 || ft_strchr_gnl(line, '\n', '\n') > -1)
			return (free(line_read), line);
	}
}

void	modify_stock(char *stock, char *line, int i)
{
	int	found;

	found = 0;
	while (line[i] != '\0')
	{
		stock[found] = line[i];
		found++;
		i++;
	}
	stock[found] = '\0';
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char		*line;
	int			found;
	char		*secline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, stock);
	if (line == NULL)
		return (ft_memset_gnl(stock, 0, sizeof(stock)), NULL);
	if (ft_strlen_gnl(line) == 0)
		return (free(line), NULL);
	found = ft_strchr_gnl(line, '\n', '\0');
	if (found == -1)
		return (free(line), NULL);
	if (line[found] == '\0')
		return (ft_memset_gnl(stock, 0, sizeof(stock)), line);
	found += 1;
	modify_stock(stock, line, found);
	secline = 0;
	secline = ft_strncpy_gnl(secline, line, found);
	return (free(line), secline);
}
