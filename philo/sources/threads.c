/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:48:10 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/15 11:46:21 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*loop(void *a)
{
	t_philo	*philo;

	philo = (t_philo *)a;
	pthread_detach(philo->t);
	philo->lasteat = philo->main->start;
	while (1)
	{
		if (eeeating(philo) == -1)
			break ;
	}
	return (NULL);
}

void	forks(t_main *main)
{
	int	i;

	i = -1;
	if (main->philocount == 1)
	{
		main->philos[0].l_fork = 0;
		main->philos[0].r_fork = 0;
		return ;
	}
	while (++i <= main->philocount)
	{
		main->philos[i].l_fork = i;
		if ((i + 1) % main->philocount == 0)
			main->philos[i].r_fork = (i + 1) % main->philocount;
		else
			main->philos[i].r_fork = i + 1;
	}
}

int	thread_start(t_main *main)
{
	int	i;

	i = 0;
	while (++i <= main->philocount)
	{
		if (i % 2)
		{
			if (pthread_create(&main->philos[i - 1].t, NULL, loop,
					(void *)&main->philos[i - 1]) != 0)
				return (1);
			usleep(50);
		}
	}
	i = 0;
	while (++i <= main->philocount)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&main->philos[i - 1].t, NULL, loop,
					(void *)&main->philos[i - 1]) != 0)
				return (1);
			usleep(50);
		}
	}
	return (0);
}
