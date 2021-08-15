/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:51:05 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/15 12:13:06 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	lockprint(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->main->write);
	printf("%ld  %d%s", get_ms(philo->main->start_time), philo->num, str);
	pthread_mutex_unlock(&philo->main->write);
}

static void	forktake(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->mutex[philo->r_fork]);
	lockprint(philo, " has taken a right fork\n");
	pthread_mutex_lock(&philo->main->mutex[philo->l_fork]);
	lockprint(philo, " has taken a left fork\n");
}

int	eeeating(t_philo *philo)
{
	if (philo->main->isdead == 0)
		return (-1);
	forktake(philo);
	if (philo->main->isdead == 0)
		return (-1);
	philo->lasteat = get_time();
	lockprint(philo, " is eating\n");
	gettimeofday(&philo->main->current, NULL);
	uusleep(philo->main->time2eat, philo->main->current, philo);
	pthread_mutex_unlock(&philo->main->mutex[philo->r_fork]);
	pthread_mutex_unlock(&philo->main->mutex[philo->l_fork]);
	if (philo->main->isdead == 0)
		return (-1);
	if (philo->count != 0)
		philo->count -= 1;
	gettimeofday(&philo->main->current, NULL);
	lockprint(philo, " is sleeping\n");
	uusleep(philo->main->time2sleep, philo->main->current, philo);
	if (philo->main->isdead == 0)
		return (-1);
	lockprint(philo, " is thinking\n");
	return (0);
}
