/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:55:21 by timanish          #+#    #+#             */
/*   Updated: 2024/10/26 19:51:00 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *p_data)
{
	long long	base;

	p_data->status = EAT;
	base = p_data->start_time;
	p_data->last_eat_time = get_time() - base;
	if (p_data->status == DIE)
		return ;
	else
		printf("%lld %d is eating\n", get_time() - base, p_data->id);
	usleep(1000 * p_data->eat_time);
	pthread_mutex_unlock(p_data->left_forks);
	pthread_mutex_unlock(p_data->right_forks);
	p_data->eat_count++;
	if (p_data->eat_count == p_data->must_eat)
		p_data->status = FIN;
}

void	philo_sleep(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->status == DIE || p_data->eat_count == p_data->must_eat)
		return ;
	else
		printf("%lld %d is sleeping\n", get_time() - base, p_data->id);
	usleep(1000 * p_data->sleep_time);
}

void	philo_think(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;

	if (p_data->status == DIE)
		return ;
	else
		printf("%lld %d is thinking\n", get_time() - base, p_data->id);
}

void	stay_philo(t_philo *p_data)
{
	philo_think(p_data);
	if (p_data->id % 2 != 0)
		usleep (1000 * (p_data->eat_time / (p_data->num / 2))
			* (p_data->id / 2));
	else
		usleep(1000 * (p_data->eat_time + (p_data->eat_time / p_data->num)
				* ((p_data->id - 1) / 2)));
}

void	*philo_routine(void *data)
{
	t_philo		*p_data;
	long long	base;

	p_data = (t_philo *)data;
	base = p_data->start_time;
	p_data->eat_count = 0;
	if (p_data->num % 2 != 0)
		stay_philo(p_data);
	while (1)
	{
		pick_up_forks(p_data);
		if (p_data->status == DIE)
			return (0);
		else
			philo_eat(p_data);
		if (p_data->status == DIE || p_data->status == FIN)
			return (0);
		else
			philo_sleep(p_data);
		if (p_data->status == DIE)
			return (0);
		else
			philo_think(p_data);
	}
	return (0);
}
