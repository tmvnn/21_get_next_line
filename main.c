/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 21:14:06 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/17 23:28:28 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <string.h>
#include "get_next_line.h"

int		main()
{
	int fd;
	char *line;

	line = 0;
	fd = open("a.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("line1 = %s\n", line);
	//get_next_line(fd, &line);
	//printf("line2 = %s\n", line);
	close (fd);
	return (0);
}
