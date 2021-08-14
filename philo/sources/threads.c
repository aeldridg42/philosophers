/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:48:10 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 12:51:42 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*loop(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	pthread_detach(philo->t);
	philo->lasteat = philo->rules->start;
	while (1)
	{
		if (eeeating(philo) == -1)
			break ;
	}
	return (NULL);
}

void	forks(t_rules *rules)
{
	int	i;

	i = -1;
	if (rules->philocount == 1)
	{
		rules->philos[0].l_fork = 0;
		rules->philos[0].r_fork = 0;
		return ;
	}
	while (++i <= rules->philocount)
	{
		rules->philos[i].l_fork = i;
		if ((i + 1) % rules->philocount == 0)
			rules->philos[i].r_fork = (i + 1) % rules->philocount;
		else
			rules->philos[i].r_fork = i + 1;
	}
}

int	thread_start(t_rules *rules)
{
	int	i;

	i = 0;
	while (++i <= rules->philocount)
	{
		if (i % 2)
		{
			if (pthread_create(&rules->philos[i - 1].t, NULL, loop,
					(void *)&rules->philos[i - 1]) != 0)
				return (1);
			usleep(50);
		}
	}
	i = 0;
	while (++i <= rules->philocount)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&rules->philos[i - 1].t, NULL, loop,
					(void *)&rules->philos[i - 1]) != 0)
				return (1);
			usleep(50);
		}
	}
	return (0);
}
