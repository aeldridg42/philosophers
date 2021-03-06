/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:28:23 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/15 12:12:23 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_ms(struct timeval current)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	new.tv_sec -= current.tv_sec;
	new.tv_usec -= current.tv_usec;
	if (new.tv_usec < 0)
	{
		new.tv_sec -= 1;
		new.tv_usec += 1000000;
	}
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

void	uusleep(long time, struct timeval now, t_philo *philo)
{
	long	cur_time;

	cur_time = get_ms(now);
	while (1)
	{
		usleep(200);
		if (get_ms(now) >= cur_time + time || !philo->main->isdead)
			break ;
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
