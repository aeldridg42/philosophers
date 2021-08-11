/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:09:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/11 20:43:44 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

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
		return (1);
	return (0);
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

static void	magicfree(t_rules *rules)
{
	if (rules->philocount == 6)
	{
		free(rules->philos);
		return ;
	}
	if (rules->philocount == 3)
	{	
		free(rules->mutex);
		free(rules->philos);
	}
	else
	{
		free(rules->philos);
		free(rules->mutex);
	}
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	if (parser(argv, argc) || init(argv, &rules, argc))
		return (1);
	forks(&rules);
	i = 0;
	while (++i <= rules.philocount)
	{
		pthread_mutex_init(&rules.mutex[i], NULL);
		rules.philos[i].num = i;
		rules.philos[i].rules = &rules;
	}
	pthread_mutex_init(&rules.write, NULL);
	gettimeofday(&rules.current1, NULL);
	rules.start = get_time();
	if (thread_start(&rules))
	{
		printf("Thread creating error.\n");
		magicfree(&rules);
		return (1);
	}
	checkphilo(&rules);
	magicfree(&rules);
	return (0);
}
