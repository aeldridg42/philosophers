/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 18:39:09 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 11:55:24 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	semaphores(t_rules *main)
{
	sem_unlink("mainname2");
	sem_unlink("takefork");
	sem_unlink("writing");
	sem_unlink("dead");
	main->sem = sem_open("mainname2", O_CREAT, 0666, main->philocount);
	main->takefork = sem_open("takefork", O_CREAT, 0666, 1);
	main->writing = sem_open("writing", O_CREAT, 0666, 1);
	main->dead = sem_open("dead", O_CREAT, 0666, 1);
}

void	init(t_rules *main, char **argv, int argc)
{
	int	i;

	i = 0;
	main->philocount = ft_atoi_s(argv[1]);
	main->time2die = ft_atoi_s(argv[2]);
	main->time2eat = ft_atoi_s(argv[3]);
	main->time2sleep = ft_atoi_s(argv[4]);
	main->numb = 1;
	main->p = malloc(sizeof(int) * main->philocount);
	if (!main->p)
		exit(1);
	while (i < main->philocount)
		main->p[i++] = -1;
	main->need2eat = -1;
	if (argc == 6)
		main->need2eat = ft_atoi_s(argv[5]);
}
