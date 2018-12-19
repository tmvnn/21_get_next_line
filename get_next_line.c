/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:28:01 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/17 23:28:23 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

int		buff_has_endl(char *buff, size_t *nl_pos)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)buff;
	i = *nl_pos;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			buff[i] = '\0'; //зануление для удобства последующего вывода
			*nl_pos = i + 1;
			return (1);
		}
		i++;
	}
	//*nl_pos = i;
	return (0);
}



int		get_next_line(const int fd, char **line)
{
	size_t			read_s;
	static size_t	nl_pos;
	char			*tmp;
	static int		old_fd;
	static char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line)
		return (-1);

	//Если предыдущий запуск был того же ФД и чтение файла было не до конца (есть остаток)
	//		Тогда
	//			Проверить Остаток на \n
	//			Создать новую строку линии и скопировать все после \n (strsub)
	//		Иначе
	//			занулить Остаток, если был (или дальше сам занулится)
	//			Переобозначить old_fd
	//
	//		Выпонять пока файл читается
	//		{
	//			Если в буффере есть \n
	//			{
	//				Добавляем в строку линии часть буфера до \n
	//				(в буффере остается последнее считывание)
	//				Прерываем цикл (break)
	//			}
	//			Добавляем в строку линии полный буфер
	//			Повтор условия цикла
	//		}
	//
	//		занулить весь буффер?????

		if (!(*line = (char *)malloc(sizeof(char))))
			return (-1);
		**line = 0;
		read_s = nl_pos;
		if (fd == old_fd && buff[nl_pos])
		{
			tmp = *line;
			if (buff_has_endl(buff, &nl_pos))
			{
				{
					if (!(*line = ft_strjoin(*line, buff + read_s)))
					{
						free(tmp);
						return (-1);
					}
					//printf("1nl: %s\n", *line);
					free(tmp);
					return (1);
				}
			}
			if (!(*line = ft_strjoin(*line, buff + read_s)))
			{
				free(tmp);
				return (-1);
			}
			//printf("10: %s\n", *line);
			free(tmp);
		}
		old_fd = fd;
		nl_pos = 0;
		while ((read_s = read(fd, buff, BUFF_SIZE)))
		{
			tmp = *line;
			buff[read_s] = 0;
			if (buff_has_endl(buff, &nl_pos))
			{
				if (!(*line = ft_strjoin(*line, buff)))
				{
					free(tmp);
					return (-1);
				}
				//printf("2nl: %s\n", *line);
				free(tmp);
				return (1);
			}
			if (!(*line = ft_strjoin(*line, buff)))
			{
				free(tmp);
				return (-1);
			}
			//printf("20: %s\n", *line);
			free(tmp);
		}
	return (0);
}
