/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:50:07 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/14 17:27:23 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int		ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

void	ft_display_file(int argc, char **av)
{
	char	buffer[29000];
	int		fdesc;
	int		i;
	int		size;

	i = 0;
	while (++i <= argc)
	{
		fdesc = open(av[i], O_RDWR);
		if (fdesc >= 0)
			while ((size = read(fdesc, &buffer, 29000)))
				write(1, &buffer, size);
		else
		{
			write(2, "cat: ", 5);
			write(2, av[i], ft_strlen(av[i]));
			if (errno != 21)
				write(2, ": No such file or directory\n", 28);
			else
				write(2, ": Is a directory\n", 17);
		}
		close(fdesc);
	}
}

int		main(int argc, char **argv)
{
	char c[4] = "asdg";

	if (argc == 1)
		while (read(0, &c, 3) > 0)
			write(1, &c, 3);
	else
		ft_display_file(argc - 1, argv);
	return (0);
}
