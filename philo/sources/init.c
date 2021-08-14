/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:10:58 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/12 17:24:56 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	checkstatus(t_rules *rules)
{
	if (rules->philocount == -1 || rules->time2die == -1
		|| rules->time2eat == -1 || rules->time2sleep == -1
		|| rules->eat_times == -1)
		return (1);
	if (rules->philocount == 0 || rules->philocount > 300)
	{
		printf("Recomended values are 1 - 200\n");
		return (1);
	}
	if (rules->eat_times == 0)
	{
		printf("Let them eat at least once, don't be greedy\n");
		return (1);
	}
	return (0);
}

int	init(char **argv, t_rules *rules, int argc)
{
	int	i;

	i = 0;
	rules->philocount = ft_atoi_s(argv[1]);
	rules->time2die = ft_atoi_s(argv[2]);
	rules->time2eat = ft_atoi_s(argv[3]);
	rules->time2sleep = ft_atoi_s(argv[4]);
	rules->isdead = 1;
	rules->eat_times = -2;
	if (argc == 6)
		rules->eat_times = ft_atoi_s(argv[5]);
	if (checkstatus(rules) == 1)
		return (1);
	rules->philos = malloc(sizeof(t_philo) * rules->philocount);
	rules->mutex = malloc(sizeof(pthread_mutex_t) * rules->philocount);
	if (!rules->philos || !rules->mutex)
	{
		printf("Memory allocating error\n");
		return (1);
	}
	while (++i <= rules->philocount)
		rules->philos[i].count = rules->eat_times;
	return (0);
}

int	mutex_init(t_rules *rules)
{
	int	i;

	i = 0;
	while (++i <= rules->philocount)
	{
		if (pthread_mutex_init(&rules->mutex[i], NULL) != 0)
		{
			printf("Mutex creating error\n");
			magicfree(rules);
			return (1);
		}
		rules->philos[i].num = i;
		rules->philos[i].rules = rules;
	}
	return (0);
}
