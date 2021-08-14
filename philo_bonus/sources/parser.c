/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:37:47 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 13:24:03 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	parser(char **argv, int argc)
{
	int	i;
	int	i2;

	if (argc != 5 && argc != 6)
	{
		printf("Usage example:\n./philo 4 410 200 200\n./philo 4 410 200 200 5\n");
		exit (1);
	}
	i = 1;
	while (--argc)
	{
		i2 = -1;
		while (argv[i][++i2])
		{
			if (!(ft_isdigit(argv[i][i2])))
			{
				printf("%s - wrong argument\n", argv[i]);
				exit (1);
			}
		}
		i++;
	}
	return (0);
}
