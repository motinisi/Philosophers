/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:32:22 by timanish          #+#    #+#             */
/*   Updated: 2024/10/21 16:36:16 by timanish         ###   ########.fr       */
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
// 	pthread_mutex_t	*left_forks;
// 	pthread_mutex_t	*right_forks;
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

// void	ft_usleep(int time)
// {
// 	int	i;

// 	i = 1001;
// 	while (--i)
// 		usleep(1 * time);
// }

void	*philo_routine(void *data)
{
	t_philo			*p_data;
	long long		base;

	p_data = (t_philo *)data;
	base = p_data->start_time;
	p_data->eat_count = 0;
	while (1)
	{
		if (p_data->id % 2 == 0)
		{
			pthread_mutex_lock(p_data->left_forks);
			if (p_data->status == DIE)
				return (0);
			else
				printf("%lld %d has taken a forks left\n",
					get_time() - base, p_data->id);
			pthread_mutex_lock(p_data->right_forks);
			if (p_data->status == DIE)
				return (0);
			else
				printf("%lld %d has taken a forks right\n",
					get_time() - base, p_data->id);
		}
		else
		{
			usleep (200);
			pthread_mutex_lock(p_data->right_forks);
			if (p_data->status == DIE)
				return (0);
			else
				printf("%lld %d has taken a forks right\n",
					get_time() - base, p_data->id);
			pthread_mutex_lock(p_data->left_forks);
			if (p_data->status == DIE)
				return (0);
			else
				printf("%lld %d has taken a forks left\n",
					get_time() - base, p_data->id);
		}
		p_data->last_eat_time = get_time() - base;
		if (p_data->status == DIE)
			return (0);
		else
		{
			printf("%lld %d is eating\n", p_data->last_eat_time, p_data->id);
		}
		usleep(1000 * p_data->eat_time);
		pthread_mutex_unlock(p_data->left_forks);
		pthread_mutex_unlock(p_data->right_forks);
		p_data->eat_count ++;
		if (p_data->status == DIE || p_data->eat_count == p_data->must_eat)
			return (0);
		else
			printf("%lld %d is sleeping\n", get_time() - base, p_data->id);
		usleep(1000 * p_data->sleep_time);
		if (p_data->status == DIE)
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
		i = 0;
		while (i < p_num)
		{
			present_time = get_time() - p_data[i].start_time;
			if (present_time - p_data[i].last_eat_time > p_data[i].die_time)
			{
				tmp = i;
				i = 0;
				while (i < p_num)
				{
					p_data[i].status = DIE;
					i ++;
				}
				printf("%lld %d died\n", present_time, p_data[tmp].id);
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
	pthread_mutex_t	*forks;
	pthread_t		monitoring_thread;
	int				p_all;
	int				i;

	p_data = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	p_all = ft_atoi(argv[1]);
	p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	i = 0;
	while (i < p_all)
	{
		p_data[i].num = ft_atoi(argv[1]);
		p_data[i].id = i + 1;
		p_data[i].start_time = get_time();
		p_data[i].die_time = ft_atoi(argv[2]);
		p_data[i].eat_time = ft_atoi(argv[3]);
		p_data[i].sleep_time = ft_atoi(argv[4]);
		if (argv[5])
			p_data[i].must_eat = ft_atoi(argv[5]);
		else
			p_data[i].must_eat = NONE;
		pthread_mutex_init(&forks[i], NULL);
		p_data[i].left_forks = &forks[i];
		p_data[i].right_forks = &forks[(i + 1) % p_all];
		p_data[i].last_eat_time = get_time();
		i ++;
	}
	i = 0;
	while (i < p_all)
	{
		pthread_create(&p_pthread[i], NULL, philo_routine, &p_data[i]);
		i ++;
	}
	pthread_create(&monitoring_thread, NULL, (void *)monitoring_philo, p_data);
	i = 0;
	// if (p_data->status == DIE)
	// {
	// 	while (i < p_all)
	// 	{
	// 		p_data[i].status = DIE;
	// 		i ++;
	// 	}
	// }
	i = 0;
	while (i < p_all)
	{
		pthread_join(p_pthread[i], NULL);
		i ++;
	}
	pthread_join(monitoring_thread, NULL);
	free(p_pthread);
	free(forks);
	free(p_data);
}


// ./philo 3 300 100 100 4 この引数バグる