/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkphilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:14:11 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 14:21:02 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	everyoneate(t_main *main)
{
	main->isdead = 0;
	pthread_mutex_lock(&main->write);
	usleep(50);
	printf(RED"%ld  everyone ate %d times\n", get_ms(main->start_time),
		main->eat_times);
}

static int	someonedead(t_main *main, int i)
{
	if (get_time() - main->philos[i - 1].lasteat > main->time2die)
	{
		main->isdead = 0;
		pthread_mutex_lock(&main->write);
		usleep(50);
		printf(RED"%ld  %d died\n", get_ms(main->start_time), i);
		return (1);
	}
	return (0);
}

void	checkphilo(t_main *main)
{
	int	i;
	int	check;

	check = 1;
	while (1)
	{
		i = 0;
		if (check == 0)
		{
			everyoneate(main);
			return ;
		}
		check = 0;
		while (++i <= main->philocount)
		{
			check += main->philos[i - 1].count;
			if (someonedead(main, i))
				return ;
		}
	}
}
