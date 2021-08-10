/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:37:47 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/10 17:36:01 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

	i = 0;
	if (argc == 5 || argc == 6)
	{
		while (--argc)
		{
			i2 = 0;
			while (argv[++i][i2])
			{
				if (!(ft_isdigit(argv[i][i2++])))
				{
					printf("%s - wrong argument\n", argv[i]);
					return (1);
				}
			}
		}
	}
	else
	{
		printf("Usage example:\n./philo 4 410 200 200\n./philo 4 410 200 200 5\n");
		return (1);
	}
	return (0);
}

int	checkvalue(t_rules *rules)
{
	if (rules->philocount > 200)
	{
		printf("%d - wrong value. Try 1-200.\n", rules->philocount);
		return (1);
	}
	return (0);
}
