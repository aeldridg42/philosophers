/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:51:05 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/12 11:48:43 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	lockprint(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->rules->write);
	printf("%ld  %d%s", get_ms(philo->rules->start_time), philo->num, str);
	pthread_mutex_unlock(&philo->rules->write);
}

static void	forktake(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->mutex[philo->r_fork]);
	lockprint(philo, " has taken a right fork\n");
	pthread_mutex_lock(&philo->rules->mutex[philo->l_fork]);
	lockprint(philo, " has taken a left fork\n");
}

int	eeeating(t_philo *philo)
{
	if (philo->rules->isdead == 0)
		return (-1);
	forktake(philo);
	if (philo->rules->isdead == 0)
		return (-1);
	philo->lasteat = get_time();
	lockprint(philo, " is eating\n");
	gettimeofday(&philo->rules->current, NULL);
	uusleep(philo->rules->time2eat, philo->rules->current);
	if (philo->rules->isdead == 0)
		return (-1);
	pthread_mutex_unlock(&philo->rules->mutex[philo->r_fork]);
	pthread_mutex_unlock(&philo->rules->mutex[philo->l_fork]);
	if (philo->rules->isdead == 0)
		return (-1);
	gettimeofday(&philo->rules->current, NULL);
	lockprint(philo, " is sleeping\n");
	if (philo->rules->isdead == 0)
		return (-1);
	uusleep(philo->rules->time2sleep, philo->rules->current);
	if (philo->rules->isdead == 0)
		return (-1);
	lockprint(philo, " is thinking\n");
	return (0);
}
