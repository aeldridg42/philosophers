/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 18:22:04 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/14 13:27:29 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>

# define RED "\x1b[31m"

typedef struct s_rules
{
	int				philocount;
	int				time2die;
	int				time2sleep;
	int				time2eat;
	int				need2eat;
	int				numb;
	int				*p;
	long			start;
	long			lasteat;
	sem_t			*sem;
	sem_t			*takefork;
	sem_t			*writing;
	sem_t			*dead;
	pthread_t		t;
	struct timeval	current;
	struct timeval	start_time;
}					t_rules;

int		parser(char **argv, int argc);
int		ft_isdigit(int c);
int		ft_isdigit(int c);
int		ft_atoi_s(const char *str);
long	get_time(void);
long	get_ms(struct timeval current);
void	uusleep(long time, struct timeval now);
void	eating(t_rules *main);
void	semaphores(t_rules *main);
void	init(t_rules *main, char **argv, int argc);
void	philo_start(t_rules *main);

#endif