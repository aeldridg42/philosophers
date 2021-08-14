/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 18:22:13 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 15:13:21 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

static void	semsclose(t_main *main)
{
	sem_unlink("mainname2");
	sem_unlink("takefork");
	sem_unlink("writing");
	sem_unlink("dead");
	sem_close(main->sem);
	sem_close(main->takefork);
	sem_close(main->writing);
	sem_post(main->dead);
	sem_close(main->dead);
}

static void	*checkeat(void *a)
{
	t_main	*main;
	int		i;

	i = 0;
	main = (t_main *)a;
	i = main->philocount - 1;
	while (i >= 0)
		waitpid(main->p[i--], 0, 0);
	if (main->deathcheck)
		return (NULL);
	printf(RED"%ld  Everyone ate %d times\n", get_ms(main->start_time),
		main->need2eat);
	semsclose(main);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_main		main;
	pthread_t	t_m;

	parser(argv, argc);
	init(&main, argv, argc);
	semaphores(&main);
	main.start = get_time();
	gettimeofday(&main.start_time, NULL);
	philo_start(&main);
	usleep(200);
	if (argc == 6)
	{
		pthread_create(&t_m, NULL, checkeat, (void *)&main);
		pthread_detach(t_m);
	}
	sem_wait(main.dead);
	main.deathcheck = 1;
	while (--main.philocount >= 0)
		kill(main.p[main.philocount], SIGKILL);
	semsclose(&main);
	free(main.p);
	return (1);
}
