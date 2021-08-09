/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeldridg <aeldridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:09:02 by aeldridg          #+#    #+#             */
/*   Updated: 2021/08/09 19:47:50 by aeldridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

// struct timeval {
// 	long    tv_sec;         /* секунды */
// 	long    tv_usec;        /* микросекунды */
// };

// typedef struct s_rules
// {

// } 				t_rules;

int get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

typedef struct s_philo
{
	pthread_t		t;
	int				l_fork;
	int				r_fork;
	int				num;
	long long				start;
	int				lasteat;
	int				count;
	struct s_rules	*rules;
} 					t_philo;

typedef struct s_rules
{
	int		philocount;
	int		time2eat;
	int		time2sleep;
	int		time2die;
	int start;
	t_philo *philos;
	pthread_mutex_t write;
	pthread_mutex_t *mutex;
} 				t_rules;

struct timeval current1;
struct timeval current;

long long get_ms(struct timeval current)
{
	struct timeval new;

	gettimeofday(&new, NULL);
	new.tv_sec -= current.tv_sec;
	new.tv_usec -= current.tv_usec;
	if (new.tv_usec < 0)
	{
		--new.tv_sec;
		new.tv_usec += 1000000;
	}
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

void uusleep(long time, struct timeval now)
{
	long long cur_time;

	cur_time = get_ms(now);
	while (1)
	{
		usleep(250);
		if (get_ms(now) >= cur_time + time)
			break ;
	}
}

void checkphilo(t_rules *rules)
{
	int i;
	int res;
	int check;

	check = 1;
	while (1)
	{
		i = 1;
		if (!check)
			exit (0);
		check = 0;
		while (i <= rules->philocount)
		{
			check += rules->philos[i].count;
			// res = get_time() - rules->philos[i].lasteat;
			if (get_time() - rules->philos[i].lasteat > rules->time2die && rules->philos[i].count != 0)
			{
				printf("%-6lld %d died\n", get_ms(current1), i);
				exit(1);
			}
			i++;
		}
	}
}

void eeeating(t_philo *philo)
{
	if (philo->count-- == 0)
		return ;
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->rules->mutex[philo->l_fork]);
		printf("%-6lld %d has taken a left fork\n", get_ms(current1), philo->num);
		pthread_mutex_lock(&philo->rules->mutex[philo->r_fork]);
		printf("%-6lld %d has taken a right fork\n", get_ms(current1), philo->num);
	}
	else
	{
		pthread_mutex_lock(&philo->rules->mutex[philo->l_fork]);
		printf("%-6lld %d takes left fork\n", get_ms(current1), philo->num);
		pthread_mutex_lock(&philo->rules->mutex[philo->r_fork]);
		printf("%-6lld %d takes right fork\n", get_ms(current1), philo->num);
	}
	philo->lasteat = get_time();
	printf("%-6lld %d is eating\n", get_ms(current1), philo->num);
	gettimeofday(&current, NULL);
	uusleep(philo->rules->time2eat, current);
	pthread_mutex_unlock(&philo->rules->mutex[philo->l_fork]);
	pthread_mutex_unlock(&philo->rules->mutex[philo->r_fork]);
	gettimeofday(&current, NULL);
	printf("%-6lld %d is sleeping\n", get_ms(current1), philo->num);
	uusleep(philo->rules->time2sleep, current);
	printf("%-6lld %d is thinking\n", get_ms(current1), philo->num);
}

void	*smth(void *a)
{
	t_philo *philo;
	t_rules rules2;

	// rules3 = *(philo2->rules2);
	philo = (t_philo *)a;
	// rules2 = *(philo2.rules);
	// printf("Hi from %d\n", philo->num);
	// printf("%d\n", philo->rules->philocount);
	// gettimeofday(&current, NULL);
	// g_time = get_time();
	// init();
	philo->lasteat = get_time();
	while (1)
	{
		eeeating(philo);
	}
	return NULL;
}

void forks(t_rules *rules)
{
	int i;

	i = 0;
	if (rules->philocount == 1)
	{
		rules->philos[1].l_fork = 1;
		rules->philos[1].r_fork = 1;
		return ;
	}
	while (++i <= rules->philocount)
	{
		rules->philos[i].l_fork = i;
		if ((i + 1) % rules->philocount == 0)
			rules->philos[i].r_fork = i + 1;
		else
			rules->philos[i].r_fork = (i + 1) % rules->philocount;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


void	parser(char **argv, int argc)
{
	int	i;
	int i2;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (--argc)
		{
			i2 = 0;
			while(argv[i][i2])
			{
				if (!(ft_isdigit(argv[i][i2++])))
				{
					printf("%s - wrong argument\n", argv[i]);
					exit(1);
				}
			}
			i++;
		}
	}
	else
	{
		printf("Usage example: ./philo 4 410 200 200\n");
		exit(1);
	}
}

void init(char **argv, t_rules *rules, int argc)
{
	int	i;

	i = 0;
	rules->philocount = atoi(argv[1]);
	rules->time2die = atoi(argv[2]);;
	rules->time2eat = atoi(argv[3]);;
	rules->time2sleep = atoi(argv[4]);;
	if (rules->philocount < 1 || rules->philocount > 200 || rules->time2die < 60
		|| rules->time2eat < 60 || rules->time2sleep < 60)
	{
		printf("Wrong value\n");
		exit(1);
	}
	rules->philos = malloc(sizeof(t_philo) * rules->philocount);
	rules->mutex = malloc(sizeof(pthread_mutex_t) * rules->philocount);
	while (++i <= rules->philocount)
	{
		if (argc == 6)
			rules->philos[i].count = atoi(argv[5]);
		else
			rules->philos[i].count = -1;
		rules->philos[i].rules = rules;
	}
}

int main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	parser(argv, argc);
	init(argv, &rules, argc);
	i = 0;
	forks(&rules);
	while (++i <= rules.philocount)
	{
		pthread_mutex_init(&rules.mutex[i], NULL);
		rules.philos[i].num = i;
	}
	i = 0;
	gettimeofday(&current1, NULL);
	// rules.start = get_time();
	while (++i <= rules.philocount)
	{
		if (i % 2)
		{
			void *a = (void *)&rules.philos[i];
			// rules.philos[i].lasteat = get_time();
			pthread_create(&rules.philos[i].t, NULL, smth, a);
			usleep(50);
		}
	}
	i = 0;
	while (++i <= rules.philocount)
	{
		if (i % 2 == 0)
		{
			void *a = (void *)&rules.philos[i];
			// rules.philos[i].lasteat = get_time();
			pthread_create(&rules.philos[i].t, NULL, smth, a);
			usleep(50);
		}
	}
	while (1)
	{
		checkphilo(&rules);
	}
}
