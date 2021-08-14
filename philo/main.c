/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:09:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 13:14:31 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

static void	destroing_mutexes(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i <= rules->philocount)
		pthread_mutex_destroy(&rules->mutex[i]);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (parser(argv, argc) || init(argv, &rules, argc))
		return (1);
	forks(&rules);
	if (mutex_init(&rules))
		return (1);
	pthread_mutex_init(&rules.write, NULL);
	gettimeofday(&rules.start_time, NULL);
	rules.start = get_time();
	if (thread_start(&rules))
	{
		printf("Thread creating error.\n");
		free(rules.philos);
		return (1);
	}
	checkphilo(&rules);
	gettimeofday(&rules.current, NULL);
	uusleep(10, rules.current);
	free(rules.philos);
	destroing_mutexes(&rules);
	return (0);
}
