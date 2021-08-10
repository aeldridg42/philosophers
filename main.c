/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:09:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/10 17:36:52 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static void	everyoneate(t_rules *rules)
{
	rules->isdead = 0;
	usleep(50);
	printf(RED"%d  everyone ate %d times\n", get_ms(rules->current1),
		rules->eat_times);
	usleep(10000);
}

static int	someonedead(t_rules *rules, int i)
{
	if (get_time() - rules->philos[i].lasteat > rules->time2die)
	{
		rules->isdead = 0;
		usleep(50);
		printf(RED"%d  %d died\n", get_ms(rules->current1), i);
		usleep(10000);
		return (1);
	}
	return (0);
}

static void	checkphilo(t_rules *rules)
{
	int	i;
	int	res;
	int	check;

	check = 1;
	while (1)
	{
		i = 0;
		if (check == 0)
		{
			everyoneate(rules);
			return ;
		}
		check = 0;
		while (++i <= rules->philocount)
		{
			if (rules->philos[i].count != 0)
			{
				check += rules->philos[i].count;
				if (someonedead(rules, i))
					return ;
			}
		}
	}
}

static int	init(char **argv, t_rules *rules, int argc)
{
	int	i;

	i = 0;
	rules->philocount = ft_atoi_s(argv[1]);
	rules->time2die = ft_atoi_s(argv[2]);
	rules->time2eat = ft_atoi_s(argv[3]);
	rules->time2sleep = ft_atoi_s(argv[4]);
	rules->isdead = 1;
	if (argc == 6)
		rules->eat_times = ft_atoi_s(argv[5]);
	else
		rules->eat_times = -2;
	if (rules->philocount == -1 || rules->time2die == -1
		|| rules->time2eat == -1 || rules->time2sleep == -1
		|| rules->eat_times == -1 || checkvalue(rules))
		return (1);
	rules->philos = malloc(sizeof(t_philo) * rules->philocount);
	rules->mutex = malloc(sizeof(pthread_mutex_t) * rules->philocount);
	while (++i <= rules->philocount)
	{
		rules->philos[i].count = rules->eat_times;
		rules->philos[i].rules = rules;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	if (parser(argv, argc) || init(argv, &rules, argc))
		return (0);
	forks(&rules);
	i = 0;
	while (++i <= rules.philocount)
	{
		pthread_mutex_init(&rules.mutex[i], NULL);
		rules.philos[i].num = i;
	}
	gettimeofday(&rules.current1, NULL);
	thread_start(&rules);
	checkphilo(&rules);
	free(rules.philos);
	free(rules.mutex);
	return (1);
}
