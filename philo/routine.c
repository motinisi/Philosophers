/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:21 by timanish          #+#    #+#             */
/*   Updated: 2024/12/15 18:46:38 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philo_eat(t_philo *p_data)
{
	long long	base;

	pthread_mutex_lock(&p_data->status_mutex);
	p_data->status = EAT;
	base = p_data->start_time;
	p_data->last_eat_time = get_time() - base;
	pthread_mutex_unlock(&p_data->status_mutex);
	if (print_messege("is eating\n", p_data))
	{
		pthread_mutex_unlock(p_data->left_forks);
		pthread_mutex_unlock(p_data->right_forks);
		return ;
	}
	usleep(1000 * p_data->eat_time);
	pthread_mutex_lock(&p_data->status_mutex);
	pthread_mutex_unlock(p_data->left_forks);
	pthread_mutex_unlock(p_data->right_forks);
	p_data->eat_count++;
	if (p_data->eat_count == p_data->must_eat)
		p_data->status = FIN;
	pthread_mutex_unlock(&p_data->status_mutex);
}

void	philo_sleep(t_philo *p_data)
{
	print_messege("is sleeping\n", p_data);
	usleep(1000 * p_data->sleep_time);
}

void	philo_think(t_philo *p_data)
{
	print_messege("is thinking\n", p_data);
}

void	stay_philo(t_philo *p_data)
{
	philo_think(p_data);
	pthread_mutex_lock(&p_data->status_mutex);
	if (p_data->id % 2 != 0)
		usleep (1000 * (p_data->eat_time / (p_data->num / 2))
			* (p_data->id / 2));
	else
		usleep(1000 * (p_data->eat_time + (p_data->eat_time / p_data->num)
				* ((p_data->id - 1) / 2)));
	pthread_mutex_unlock(&p_data->status_mutex);
}

int	status_check(t_philo *p_data)
{
	pthread_mutex_lock(&p_data->status_mutex);
	if (p_data->status == DIE || p_data->status == FIN)
	{
		pthread_mutex_unlock(&p_data->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&p_data->status_mutex);
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo		*p_data;


	p_data = (t_philo *)data;
	p_data->eat_count = 0;
	if (p_data->num % 2 != 0)
		stay_philo(p_data);
	while (1)
	{
		pick_up_forks(p_data);
		if (status_check(p_data))
		{
			pthread_mutex_unlock(p_data->left_forks);
			pthread_mutex_unlock(p_data->right_forks);
			return (0);
		}
		philo_eat(p_data);
		if (status_check(p_data))
			return (0);
		philo_sleep(p_data);
		if (status_check(p_data))
			return (0);
		philo_think(p_data);
	}
	return (0);
}
