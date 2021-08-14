/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 18:29:12 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 15:02:47 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	*checkdeath(void *a)
{
	t_main	*main;

	main = (t_main *)a;
	pthread_detach(main->t);
	while (1)
	{
		if (get_time() - main->lasteat > main->time2die)
		{
			if (main->numb == 1)
				sem_post(main->dead);
			sem_wait(main->writing);
			printf(RED"%ld  %d is dead\n", get_ms(main->start_time), main->numb);
		}
	}
}

static void	lockprint(t_main *main, char *str)
{
	sem_wait(main->writing);
	printf("%ld  %d%s", get_ms(main->start_time), main->numb, str);
	sem_post(main->writing);
}

void	eating(t_main *main)
{
	main->lasteat = main->start;
	pthread_create(&main->t, NULL, checkdeath, (void *)main);
	while (main->need2eat--)
	{
		sem_wait(main->takefork);
		sem_wait(main->sem);
		lockprint(main, " took left fork\n");
		sem_wait(main->sem);
		lockprint(main, " took right fork\n");
		sem_post(main->takefork);
		main->lasteat = get_time();
		lockprint(main, " is eating\n");
		gettimeofday(&main->current, NULL);
		uusleep(main->time2eat, main->current);
		sem_post(main->sem);
		sem_post(main->sem);
		lockprint(main, " is sleeping\n");
		gettimeofday(&main->current, NULL);
		uusleep(main->time2sleep, main->current);
		lockprint(main, " is thinking\n");
	}
	exit(1);
}
