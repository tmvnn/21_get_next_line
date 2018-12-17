/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 22:37:47 by lbellona          #+#    #+#             */
/*   Updated: 2018/12/04 00:02:20 by lbellona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(const char *str)
{
	int					s;
	int					sign;
	unsigned long long	rez;

	s = 0;
	while (str[s] == 32 || (str[s] >= 9 && str[s] <= 13))
		s++;
	sign = 1;
	if (str[s] == 43 || str[s] == 45)
	{
		if (str[s] == 45)
			sign = -1;
		s++;
	}
	rez = 0;
	while (str[s] >= 48 && str[s] <= 57)
	{
		rez = rez * 10 + str[s] - 48;
		s++;
		if (rez > 9223372036854775807)
			return (sign == 1 ? -1 : 0);
	}
	return (sign * (int)rez);
}
