/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:10:58 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 14:27:48 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	checkstatus(t_main *main)
{
	if (main->philocount == -1 || main->time2die == -1
		|| main->time2eat == -1 || main->time2sleep == -1
		|| main->eat_times == -1)
		return (1);
	if (main->philocount == 0 || main->philocount > 300)
	{
		printf("Recomended values are 1 - 200\n");
		return (1);
	}
	if (main->eat_times == 0)
	{
		printf("Let them eat at least once, don't be greedy\n");
		return (1);
	}
	return (0);
}

int	init(char **argv, t_main *main, int argc)
{
	int	i;

	i = 0;
	main->philocount = ft_atoi_s(argv[1]);
	main->time2die = ft_atoi_s(argv[2]);
	main->time2eat = ft_atoi_s(argv[3]);
	main->time2sleep = ft_atoi_s(argv[4]);
	main->isdead = 1;
	main->eat_times = -2;
	if (argc == 6)
		main->eat_times = ft_atoi_s(argv[5]);
	if (checkstatus(main) == 1)
		return (1);
	main->philos = malloc(sizeof(t_philo) * main->philocount);
	main->mutex = malloc(sizeof(pthread_mutex_t) * main->philocount);
	if (!main->philos || !main->mutex)
	{
		printf("Memory allocating error\n");
		return (1);
	}
	while (++i <= main->philocount)
		main->philos[i - 1].count = main->eat_times;
	return (0);
}

int	mutex_init(t_main *main)
{
	int	i;

	i = 0;
	while (++i <= main->philocount)
	{
		if (pthread_mutex_init(&main->mutex[i - 1], NULL) != 0)
		{
			printf("Mutex creating error\n");
			return (1);
		}
		main->philos[i - 1].num = i;
		main->philos[i - 1].main = main;
	}
	return (0);
}
