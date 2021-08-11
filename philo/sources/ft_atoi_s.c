/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 12:04:13 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/10 17:34:03 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi_s(const char *str)
{
	long	i;
	long	int_max;
	int		neg;
	char	*copy;

	i = 0;
	neg = 1;
	int_max = 2147483647;
	copy = (char *)str;
	while (ft_isdigit(*str))
	{
		i = i * 10 + *str++ - '0';
		if ((i > int_max + 1 && neg == -1) || (i > int_max && neg == 1))
		{
			printf("%s - wrong value. Try 60 - MAX_INT.\n", copy);
			return (-1);
		}
	}
	if (i == 0)
	{	
		printf("%s - wrong value. Try 1 - MAX_INT(1-200 for philosophers).\n",
			copy);
		return (-1);
	}
	return ((int)i * neg);
}
