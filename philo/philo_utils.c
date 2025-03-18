/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:15:16 by timanish          #+#    #+#             */
/*   Updated: 2025/03/18 14:14:02 by timanish         ###   ########.fr       */
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

	pthread_mutex_lock(&p_data->status_mutex);
	base = p_data->start_time;
	if (p_data->status == DIE)
	{
		pthread_mutex_unlock(&p_data->status_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_lock(p_data->print_mutex);
		printf("%lld %d %s", get_time() - base, p_data->id, messege);
		pthread_mutex_unlock(p_data->print_mutex);
	}
	pthread_mutex_unlock(&p_data->status_mutex);
	return (0);
}

int	argment_check(char **argv)
{
	size_t	i;
	long	flag;

	i = 0;
	while (argv[++i])
	{
		flag = ft_atoi(argv[i]);
		if (flag < 0)
		{
			printf("philo_number is incorect\n");
			return (1);
		}
	}
	return (0);
}

void	cleanup(pthread_t *p_pthread, pthread_mutex_t *forks, t_philo *p_data)
{
	int	p_all;
	int	i;

	pthread_mutex_lock(&p_data->status_mutex);
	p_all = p_data[0].num;
	pthread_mutex_unlock(&p_data->status_mutex);
	i = 0;
	pthread_mutex_destroy(p_data[i].print_mutex);
	while (i < p_all)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&p_data[i].status_mutex);
		i ++;
	}
	free(p_pthread);
	free(forks);
	free(p_data);
}
