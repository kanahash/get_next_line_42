/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 22:40:16 by kanahash          #+#    #+#             */
/*   Updated: 2025/01/08 01:22:28 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_getc(int fd)
{
	static unsigned char	buf[BUFFER_SIZE];
	static unsigned char	*bufp = buf;
	static int				n = 0;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (READ_ERROR);
		if (n == 0)
			return (EOF);
		bufp = buf;
	}
	if (--n >= 0)
		return (*bufp++);
	return (EOF);
}

static char	*make_new_line(char *str, char c)
{
	char	temp[2];
	char	*new_str;

	temp[0] = c;
	temp[1] = '\0';
	if (str == NULL)
		new_str = ft_strjoin("", temp);
	else
		new_str = ft_strjoin(str, temp);
	return (new_str);
}

static char	*read_line(int fd)
{
	char	*result;
	char	c;
	char	*new_line;

	result = NULL;
	c = ft_getc(fd);
	while (c != '\0' && c != READ_ERROR)
	{
		new_line = make_new_line(result, c);
		if (!new_line)
		{
			free(result);
			return (NULL);
		}
		free(result);
		result = new_line;
		if (c == '\n')
			break ;
		c = ft_getc(fd);
	}
	return (result);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (read_line(fd));
}
