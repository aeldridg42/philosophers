/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:09:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/12 16:13:35 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

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
		magicfree(&rules);
		return (1);
	}
	checkphilo(&rules);
	magicfree(&rules);
	return (0);
}
