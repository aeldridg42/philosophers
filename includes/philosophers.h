/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:30:59 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/10 17:36:13 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

# define RED "\x1b[31m"

typedef struct s_philo
{
	pthread_t		t;
	int				l_fork;
	int				r_fork;
	int				num;
	int				lasteat;
	int				count;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	int				philocount;
	int				time2eat;
	int				time2sleep;
	int				time2die;
	int				eat_times;
	int				isdead;
	t_philo			*philos;
	struct timeval	current1;
	struct timeval	current;
	pthread_mutex_t	write;
	pthread_mutex_t	*mutex;
}					t_rules;

int		get_ms(struct timeval current);
void	uusleep(long time, struct timeval now);
int		get_time(void);
int		checkvalue(t_rules *rules);
int		parser(char **argv, int argc);
void	forks(t_rules *rules);
void	thread_start(t_rules *rules);
void	*smth(void *a);
int		eeeating(t_philo *philo);
int		ft_atoi_s(const char *str);
int		ft_isdigit(int c);

#endif