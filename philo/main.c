/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:32:22 by timanish          #+#    #+#             */
/*   Updated: 2024/10/14 20:35:35 by timanish         ###   ########.fr       */
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
// 	long long		start_time;
// 	long long		last_eat_time;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// }	t_philo;

// void	philo_state(void *arg)
// {

// }

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return (time);
}

// int	print_messege(char *message, t_philo p_data)
// {

// }

void	*philo_routine(void *data)
{
	t_philo			*p_data;
	long long		base;

	p_data = (t_philo *)data;
	base = p_data->start_time;
	p_data->eat_count = 0;
	// printf("philo_routine : so far ok\n");
	while (1)
	{
		if (p_data->id % 2 == 0)
		{
			pthread_mutex_lock(p_data->left_fork);
			if (p_data->stateus == DIE)
				return (0);
			else
				printf("%lld %d has taken a fork\n", get_time() - base, p_data->id);
			pthread_mutex_lock(p_data->right_fork);
			if (p_data->stateus == DIE)
				return (0);
			else
				printf("%lld %d has taken a fork\n", get_time() - base, p_data->id);
		}
		else
		{
			pthread_mutex_lock(p_data->right_fork);
			if (p_data->stateus == DIE)
				return (0);
			printf("%lld %d has taken a fork\n", get_time() - base, p_data->id);
			pthread_mutex_lock(p_data->left_fork);
			if (p_data->stateus == DIE)
				return (0);
			else
				printf("%lld %d has taken a fork\n", get_time() - base, p_data->id);
		}
		if (p_data->stateus == DIE)
			return (0);
		else
			printf("%lld %d is eating\n", get_time() - base, p_data->id);
		usleep(1000 * p_data->eat_time);
		p_data->last_eat_time = get_time();
		pthread_mutex_unlock(p_data->left_fork);
		pthread_mutex_unlock(p_data->right_fork);
		p_data->eat_count ++;
		if (p_data->stateus == DIE || p_data->eat_count == p_data->must_eat)
			return (0);
		else
			printf("%lld %d is sleeping\n", get_time() - base, p_data->id);
		usleep(1000 * p_data->sleep_time);
		if (p_data->stateus == DIE)
			return (0);
		else
			printf("%lld %d is thinking\n", get_time() - base, p_data->id);
	}
	return (0);
}

void	monitoring_philo(t_philo *p_data)
{
	long long	present_time;
	int			p_num;
	int			fin_eat_num;
	int			i;
	int			tmp;

	p_num = p_data->num;
	while (1)
	{
		present_time = get_time();
		i = 0;
		while (i < p_num)
		{
			// printf("last eat time %lld\n", p_data[i].last_eat_time);
			if (present_time - p_data[i].last_eat_time > p_data[i].die_time)
			{
				// p_data[i].stateus = DIE;
				// p_data->stateus = DIE;
				tmp = 0;
				tmp = i;
				i = 0;
				while (i < p_num)
				{
					p_data[i].stateus = DIE;
					i ++;
				}
				printf("%lld %d died\n", (present_time - p_data[tmp].start_time),
					p_data[tmp].id);
				return ;
			}
			i ++;
		}
		i = 0;
		fin_eat_num = 0;
		while (i < p_num)
		{
			if (p_data[i].eat_count == p_data[i].must_eat)
				fin_eat_num ++;
			i ++;
		}
		if (fin_eat_num == p_num)
			return ;
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*fork;
	pthread_t		monitoring_thread;
	int				i;

	p_data = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	p_data->num = ft_atoi(argv[1]);
	p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * p_data->num);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p_data->num);
	i = 0;
	while (i < p_data->num)
	{
		p_data[i].id = i + 1;
		p_data[i].start_time = get_time();
		p_data[i].die_time = ft_atoi(argv[2]);
		p_data[i].eat_time = ft_atoi(argv[3]);
		p_data[i].sleep_time = ft_atoi(argv[4]);
		p_data[i].must_eat = ft_atoi(argv[5]);
		pthread_mutex_init(&fork[i], NULL);
		p_data[i].left_fork = &fork[i];
		p_data[i].right_fork = &fork[(i + 1) % p_data->num];
		p_data[i].last_eat_time = get_time();
		i ++;
	}
	i = 0;
	while (i < p_data->num)
	{
		pthread_create(&p_pthread[i], NULL, philo_routine, &p_data[i]);
		i ++;
	}
	pthread_create(&monitoring_thread, NULL, (void *)monitoring_philo, p_data);
	i = 0;
	pthread_join(monitoring_thread, NULL);
	// if (p_data->stateus == DIE)
	// {
	// 	while (i < p_data->num)
	// 	{
	// 		p_data[i].stateus = DIE;
	// 		i ++;
	// 	}
	// }
	i = 0;
	while (i < p_data->num)
	{
		pthread_join(p_pthread[i], NULL);
		i ++;
	}
	free(p_pthread);
	free(fork);
	free(p_data);
}
