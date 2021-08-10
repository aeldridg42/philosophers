/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:48:10 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/10 17:24:48 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*smth(void *a)
{
	t_philo	*philo;
	t_rules	rules2;

	philo = (t_philo *)a;
	pthread_detach(philo->t);
	philo->lasteat = get_time();
	while (1)
	{
		if (philo->count != 0)
			philo->count -= 1;
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

void	thread_start(t_rules *rules)
{
	int	i;

	i = 0;
	while (++i <= rules->philocount)
	{
		if (i % 2)
		{
			pthread_create(&rules->philos[i].t, NULL, smth,
				(void *)&rules->philos[i]);
			usleep(50);
		}
	}
	i = 0;
	while (++i <= rules->philocount)
	{
		if (i % 2 == 0)
		{
			pthread_create(&rules->philos[i].t, NULL, smth,
				(void *)&rules->philos[i]);
			usleep(50);
		}
	}
}
