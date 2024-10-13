/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:59:51 by timanish          #+#    #+#             */
/*   Updated: 2024/10/13 19:23:28 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// typedef struct s_philo
// {
// 	int				id;
// 	int				state;
// 	int				die_time;
// 	int				eat_time;
// 	int				sleep_time;
// 	int				fin_eat_time;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// }	t_philo;

// void	philo_state(void *arg)
// {

// }

int	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return (time);
}

void	*philo_routine(void *arg)
{
	t_philo			*p_data;
	long long		base;

	base = get_time();
	p_data = (t_philo *)arg;
	while (1)
	{
		// printf("msec ; %lld\n", get_time() - base);
		printf("%lld %d is eating\n", get_time() - base, p_data->id);
		if (p_data->id % 2 == 0)
		{
			pthread_mutex_lock(p_data->left_fork);
			pthread_mutex_lock(p_data->right_fork);
		}
		else
		{
			pthread_mutex_lock(p_data->right_fork);
			pthread_mutex_lock(p_data->left_fork);
		}
		usleep(1000 * p_data->eat_time);
		pthread_mutex_unlock(p_data->left_fork);
		pthread_mutex_unlock(p_data->right_fork);
		printf("%lld %d is sleeping\n", get_time() - base, p_data->id);
		usleep(1000 * p_data->sleep_time);
		printf("%lld %d is thinking\n", get_time() - base, p_data->id);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				total_p;
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*fork;
	size_t			i;

	total_p = ft_atoi(argv[1]);
	p_data = (t_philo *)malloc(sizeof(t_philo) * total_p);
	p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * total_p);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_p);
	p_data->eat_time = ft_atoi(argv[3]);
	p_data->sleep_time = ft_atoi(argv[4]);
	i = 0;
	while (i < total_p)
	{
		pthread_mutex_init(&fork[i], NULL);
		i ++;
	}
	i = 0;
	while (i < total_p)
	{
		p_data[i].id = i + 1;
		p_data[i].left_fork = &fork[i - 1];
		if (i == 0)
			p_data[i].left_fork = &fork[total_p - 1];
		p_data[i].right_fork = &fork[i];
		pthread_create(&p_pthread[i], NULL, philo_routine, &p_data[i]);
		i ++;
	}
	i = 0;
	while (i < total_p)
	{
		pthread_join(p_pthread[i], NULL);
		i ++;
	}
	i = 0;
	while (i < total_p)
	{
		pthread_mutex_destroy(&fork[i]);
		i ++;
	}
	return (0);
}
