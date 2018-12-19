/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:28:01 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/19 18:26:51 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		buff_has_endl(char *buff, size_t *nl_pos)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)buff;
	i = *nl_pos;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			buff[i] = '\0';
			*nl_pos = i + 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int		read_line(char **line, char *buff, size_t *nl_pos, size_t start_p)
{
	char	*tmp;

	tmp = *line;
	if (buff_has_endl(buff, nl_pos))
	{
		if (!(*line = ft_strjoin(*line, buff + start_p)))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
		return (1);
	}
	if (!(*line = ft_strjoin(*line, buff + start_p)))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (2);
}

int		get_next_line(const int fd, char **line)
{
	int				read_s;
	static size_t	nl_pos;
	int				ret_value;
	static int		old_fd;
	static char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || !(*line = (char *)malloc(sizeof(char))))
		return (-1);
	ret_value = 0;
	**line = 0;
	if (fd == old_fd && nl_pos && buff[nl_pos])
		if ((ret_value = read_line(line, buff, &nl_pos, nl_pos)) < 2)
			return (ret_value);
	old_fd = fd;
	nl_pos = 0;
	while ((read_s = read(fd, buff, BUFF_SIZE)))
	{
		if (read_s < 0)
			return (-1);
		buff[read_s] = 0;
		if ((ret_value = read_line(line, buff, &nl_pos, 0)) < 2)
			return (ret_value);
	}
	return (ret_value > 0 ? 1 : 0);
}
