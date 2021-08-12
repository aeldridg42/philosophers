/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magicfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:12:49 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/12 16:13:30 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	magicfree(t_rules *rules)
{
	if (rules->philocount == 6)
	{
		free(rules->philos);
		return ;
	}
	if (rules->philocount == 3)
	{
		free(rules->mutex);
		free(rules->philos);
	}
	else
	{
		free(rules->philos);
		free(rules->mutex);
	}
}
