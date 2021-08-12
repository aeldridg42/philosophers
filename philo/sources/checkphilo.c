/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:14:11 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/12 16:06:42 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	everyoneate(t_rules *rules)
{
	rules->isdead = 0;
	pthread_mutex_lock(&rules->write);
	usleep(50);
	printf(RED"%ld  everyone ate %d times\n", get_ms(rules->start_time),
		rules->eat_times);
}

static int	someonedead(t_rules *rules, int i)
{
	if (get_time() - rules->philos[i].lasteat > rules->time2die)
	{
		rules->isdead = 0;
		pthread_mutex_lock(&rules->write);
		usleep(50);
		printf(RED"%ld  %d died\n", get_ms(rules->start_time), i);
		return (1);
	}
	return (0);
}

void	checkphilo(t_rules *rules)
{
	int	i;
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
			check += rules->philos[i].count;
			if (someonedead(rules, i))
				return ;
		}
	}
}
