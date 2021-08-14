/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:30:59 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 12:58:31 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\x1b[31m"

typedef struct s_philo
{
	pthread_t		t;
	int				l_fork;
	int				r_fork;
	int				num;
	int				count;
	long			lasteat;
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
	long			start;
	t_philo			*philos;
	struct timeval	current;
	struct timeval	start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	*mutex;
}					t_rules;

int		checkvalue(t_rules *rules);
int		parser(char **argv, int argc);
int		eeeating(t_philo *philo);
int		ft_atoi_s(const char *str);
int		ft_isdigit(int c);
int		thread_start(t_rules *rules);
int		mutex_init(t_rules *rules);
int		init(char **argv, t_rules *rules, int argc);
long	get_ms(struct timeval current);
long	get_time(void);
void	*loop(void *a);
void	forks(t_rules *rules);
void	checkphilo(t_rules *rules);
void	uusleep(long time, struct timeval now);

#endif