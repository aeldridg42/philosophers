/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainproc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:51:05 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/10 17:10:15 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	oddoreven(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->rules->mutex[philo->l_fork]);
		if (philo->rules->isdead)
			printf("%d  %d has taken a left fork\n",
				get_ms(philo->rules->current1), philo->num);
		pthread_mutex_lock(&philo->rules->mutex[philo->r_fork]);
		if (philo->rules->isdead)
			printf("%d  %d has taken a right fork\n",
				get_ms(philo->rules->current1), philo->num);
	}
	else
	{
		if (philo->rules->isdead)
			pthread_mutex_lock(&philo->rules->mutex[philo->l_fork]);
		if (philo->rules->isdead)
			printf("%d  %d takes left fork\n",
				get_ms(philo->rules->current1), philo->num);
		pthread_mutex_lock(&philo->rules->mutex[philo->r_fork]);
		if (philo->rules->isdead)
			printf("%d  %d takes right fork\n",
				get_ms(philo->rules->current1), philo->num);
	}
}

int	eeeating(t_philo *philo)
{
	oddoreven(philo);
	philo->lasteat = get_time();
	if (philo->rules->isdead)
		printf("%d  %d is eating\n", get_ms(philo->rules->current1), philo->num);
	gettimeofday(&philo->rules->current, NULL);
	uusleep(philo->rules->time2eat, philo->rules->current);
	pthread_mutex_unlock(&philo->rules->mutex[philo->l_fork]);
	pthread_mutex_unlock(&philo->rules->mutex[philo->r_fork]);
	gettimeofday(&philo->rules->current, NULL);
	if (philo->rules->isdead)
		printf("%d  %d is sleeping\n", get_ms(philo->rules->current1),
			philo->num);
	uusleep(philo->rules->time2sleep, philo->rules->current);
	if (philo->rules->isdead)
		printf("%d  %d is thinking\n", get_ms(philo->rules->current1),
			philo->num);
	if (philo->rules->isdead == 0)
		return (-1);
	return (0);
}
