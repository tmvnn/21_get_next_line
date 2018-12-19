/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 21:14:06 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/19 18:03:59 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <string.h>
#include "get_next_line.h"

int		main()
{
	int fd;
	char *line;
	int i;

	line = 0;
	fd = open("WaP.txt", O_RDONLY);
	i = 0;
	//printf("%d\n", get_next_line(fd, &line));
	//printf("line = %s\n", line);
	//printf("len = %lu\n", ft_strlen(line));
	int counter = 0;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		counter++;
		//i = get_next_line(fd, &line);
		//printf("%d\n", i);
		//printf("line = %s\n", line);
	}
	printf("%d\n", counter);
	/*
	printf("gnl = %d\n", get_next_line(fd, &line));
	printf("line1 = %s\n", line);
	printf("gnl = %d\n", get_next_line(fd, &line));
	printf("line2 = %s\n", line);
	printf("gnl = %d\n", get_next_line(fd, &line));
	printf("line3 = %s\n", line);
	*/

	close (fd);
	return (0);
}
