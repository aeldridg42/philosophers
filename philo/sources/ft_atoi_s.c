/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 12:04:13 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/11 20:22:01 by aeldridg         ###   ########.fr       */
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
			printf("%s - is greater that MAX_INT.\n", copy);
			return (-1);
		}
	}
	return ((int)i * neg);
}
