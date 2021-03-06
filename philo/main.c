/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:09:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/15 12:37:48 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static void	destroing_mutexes(t_main *main)
{
	int	i;

	i = -1;
	while (++i < main->philocount)
		pthread_mutex_destroy(&main->mutex[i]);
	pthread_mutex_destroy(&main->write);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (parser(argv, argc) || init(argv, &main, argc))
		return (1);
	forks(&main);
	if (mutex_init(&main))
		return (1);
	gettimeofday(&main.start_time, NULL);
	main.start = get_time();
	if (thread_start(&main))
	{
		printf("Thread creating error.\n");
		free(main.philos);
		return (1);
	}
	checkphilo(&main);
	gettimeofday(&main.current, NULL);
	usleep(200);
	free(main.philos);
	destroing_mutexes(&main);
	return (0);
}
