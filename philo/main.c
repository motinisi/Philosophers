/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisi <nisi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:01:58 by timanish          #+#    #+#             */
/*   Updated: 2024/10/26 11:01:12 by nisi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return (time);
}

int	print_messege(char *messege, t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->status == DIE)
		return (1);
	else
		printf("%lld %d %s", get_time() - base, p_data->id, messege);
	return (0);
}

void	even_pick_up_forks(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->id % 2 == 0)
	{
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork left\n", p_data))
			return ;
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork right\n", p_data))
			return ;
	}
	else
	{
		// usleep(1000);
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork right\n", p_data))
			return ;
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork left\n", p_data))
			return ;
	}
}

void	odd_pick_up_forks(t_philo *p_data)
{
	long long	base;
	t_philo		*prev;

	base = p_data->start_time;
	prev = p_data->prev;
	if (p_data->id % 2 != 0)
	{
		usleep (1000 * (p_data->eat_time / (p_data->num / 2))
			* (p_data->id / 2));
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork left\n", p_data))
			return ;
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork right\n", p_data))
			return ;
	}
	else
	{
		// printf("\nid : %d\n\n", prev->id);
		// printf("\nstatus : %d\n\n", prev->status);
		
		usleep(1000 * p_data->eat_time);
		// usleep(1000 * (p_data->eat_time + (p_data->eat_time / p_data->num) *
		// 	((p_data->id - 1) / 2)));
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork left\n", p_data))
			return ;
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork right\n", p_data))
			return ;
	}
}

int	check_death(t_philo *p_data)
{
	long long	present_time;
	int			p_num;
	int			i;
	int			tmp;

	p_num = p_data[0].num;
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
				i++;
			}
			printf("%lld %d died\n", present_time, p_data[tmp].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_eaten(t_philo *p_data)
{
	int	p_num;
	int	i;
	int	fin_eat_num;

	p_num = p_data[0].num;
	i = 0;
	fin_eat_num = 0;
	while (i < p_num)
	{
		if (p_data[i].eat_count == p_data[i].must_eat)
			fin_eat_num++;
		i++;
	}
	if (fin_eat_num == p_num)
		return (1);
	return (0);
}

void	monitoring_philo(t_philo *p_data)
{
	while (1)
	{
		if (check_death(p_data))
			return ;
		if (check_all_eaten(p_data))
			return ;
		usleep(1000);
	}
}

void	cleanup(pthread_t *p_pthread, pthread_mutex_t *forks, t_philo *p_data)
{
	int	p_all;
	int	i;

	p_all = p_data[0].num;
	i = 0;
	while (i < p_all)
	{
		pthread_mutex_destroy(&forks[i]);
		i ++;
	}
	free(p_pthread);
	free(forks);
	free(p_data);
}

int	main(int argc, char **argv)
{
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*forks;
	pthread_t		monitoring_thread;

	init_philosophers(&p_data, argc, argv, &forks);
	create_philosopher_threads(&p_pthread, p_data);
	pthread_create(&monitoring_thread, NULL, (void *)monitoring_philo, p_data);
	join_philosopher_threads(p_pthread, p_data);
	pthread_join(monitoring_thread, NULL);
	cleanup(p_pthread, forks, p_data);
	return (0);
}
