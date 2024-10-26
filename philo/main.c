/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:01:58 by timanish          #+#    #+#             */
/*   Updated: 2024/10/26 19:10:05 by timanish         ###   ########.fr       */
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

void	pick_up_forks(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->id % 2 == 0)
	{
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork\n", p_data))
			return ;
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork\n", p_data))
			return ;
	}
	else
	{
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork\n", p_data))
			return ;
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork\n", p_data))
			return ;
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
