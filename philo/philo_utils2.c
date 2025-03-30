/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:53:15 by timanish          #+#    #+#             */
/*   Updated: 2025/03/30 22:24:12 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *p_data)
{
	if (p_data->num == 3)
	{
		if (pickup_forks_for_edge_cases(p_data))
			return ;
	}
	else if (p_data->id % 2 == 0)
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

int	pickup_forks_for_edge_cases(t_philo *p_data)
{
	pthread_mutex_lock(p_data->right_forks);
	if (print_messege("has taken a fork\n", p_data))
		return (1);
	pthread_mutex_lock(p_data->left_forks);
	if (print_messege("has taken a fork\n", p_data))
		return (1);
	return (0);
}

int	one_philo_logic(t_philo *p_data)
{
	printf("%lld %d %s", get_time() - p_data->start_time,
		p_data->id, "has taken a fork\n");
	usleep(1000 * p_data->die_time);
	printf("%d %d %s", p_data->die_time, p_data->id, "died\n");
	return (1);
}
