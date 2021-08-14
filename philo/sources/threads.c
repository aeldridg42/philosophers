/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:48:10 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/13 13:24:11 by aeldridg         ###   ########.fr       */
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

	i = 0;
	if (rules->philocount == 1)
	{
		rules->philos[1].l_fork = 1;
		rules->philos[1].r_fork = 1;
		return ;
	}
	while (++i <= rules->philocount)
	{
		rules->philos[i].l_fork = i;
		if ((i + 1) % rules->philocount == 0)
			rules->philos[i].r_fork = i + 1;
		else
			rules->philos[i].r_fork = (i + 1) % rules->philocount;
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
			if (pthread_create(&rules->philos[i].t, NULL, loop,
					(void *)&rules->philos[i]) != 0)
				return (1);
			usleep(50);
		}
	}
	i = 0;
	while (++i <= rules->philocount)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&rules->philos[i].t, NULL, loop,
					(void *)&rules->philos[i]) != 0)
				return (1);
			usleep(50);
		}
	}
	return (0);
}
