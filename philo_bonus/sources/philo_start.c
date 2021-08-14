/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 18:51:12 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/13 20:28:22 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	philo_start(t_rules *main)
{
	int	i;

	i = 0;
	while (i < main->philocount)
	{
		main->p[i] = fork();
		if (main->p[i] == 0)
		{
			if (i == 0)
				sem_wait(main->dead);
			eating(main);
		}
		else
		{
			main->numb++;
			i++;
		}
	}
}
