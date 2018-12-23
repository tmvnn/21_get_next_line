/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 18:12:32 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/23 18:31:47 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list		*get_file(t_list **files, int fd)
{
	t_list			*tmp_l;

	tmp_l = *files;
	while (tmp_l)
	{
		if (fd == (int)tmp_l->content_size)
			return (tmp_l);
		tmp_l = tmp_l->next;
	}
	tmp_l = ft_lstnew("\0", fd);
	ft_lstadd(files, tmp_l);
	return (*files);
}

static int			str_free_and_realloc(char **oldstr, char *newstr)
{
	char			*tmp;

	tmp = *oldstr;
	if (!newstr)
		return (0);
	*oldstr = newstr;
	free(tmp);
	return (1);
}

static int			read_line(char **line, char **content)
{
	char			*nl_pos;

	if ((nl_pos = ft_strchr(*content, '\n')))
	{
		*nl_pos = '\0';
		str_free_and_realloc(line, ft_strjoin(*line, *content));
		str_free_and_realloc(content, ft_strdup(nl_pos + 1));
		return (1);
	}
	str_free_and_realloc(line, ft_strjoin(*line, *content));
	str_free_and_realloc(content, ft_strdup(*content + ft_strlen(*content)));
	return (2);
}

int					get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	int				read_s;
	int				ret_value;
	static t_list	*files;
	t_list			*cur_f;

	if (fd < 0 || !line)
		return (-1);
	if (!(*line = (char *)malloc(sizeof(char))) || read(fd, buff, 0) < 0)
		return (-1);
	cur_f = get_file(&files, fd);
	**line = 0;
	ret_value = 0;
	if (*(char*)(cur_f->content))
		if ((ret_value = read_line(line, (char **)&cur_f->content)) < 2)
			return (ret_value);
	while ((read_s = read(fd, buff, BUFF_SIZE)))
	{
		buff[read_s] = '\0';
		str_free_and_realloc((char **)&cur_f->content,
				ft_strjoin(cur_f->content, buff));
		if ((ret_value = read_line(line, (char **)&cur_f->content)) < 2)
			return (ret_value);
	}
	return (ret_value > 0 ? 1 : 0);
}
