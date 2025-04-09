/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:53:15 by timanish          #+#    #+#             */
/*   Updated: 2025/04/09 16:49:50 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks_for_normal_cases(t_philo *p_data)
{
	if (p_data->id % 2 == 0)
	{
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork\n", p_data))
		{
			pthread_mutex_lock(p_data->right_forks);
			return ;
		}
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork\n", p_data))
			return ;
	}
	else
	{
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork\n", p_data))
		{
			pthread_mutex_lock(p_data->left_forks);
			return ;
		}
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork\n", p_data))
			return ;
	}
}

void	pick_up_forks(t_philo *p_data)
{
	if (p_data->num == 3 || p_data->num == 1)
	{
		if (pickup_forks_for_edge_cases(p_data))
			return ;
	}
	else
		pick_up_forks_for_normal_cases(p_data);
}

int	pickup_forks_for_edge_cases(t_philo *p_data)
{
	pthread_mutex_lock(p_data->right_forks);
	if (print_messege("has taken a fork\n", p_data))
	{
		pthread_mutex_lock(p_data->left_forks);
		return (1);
	}
	if (p_data->num == 1)
	{
		one_philo_logic(p_data);
		return (0);
	}
	pthread_mutex_lock(p_data->left_forks);
	if (print_messege("has taken a fork\n", p_data))
		return (1);
	return (0);
}

int	one_philo_logic(t_philo *p_data)
{
	while (1)
	{
		pthread_mutex_lock(&p_data->status_mutex);
		if (p_data->status == DIE)
		{
			pthread_mutex_unlock(&p_data->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&p_data->status_mutex);
		usleep(1000);
	}
	pthread_mutex_unlock(p_data->right_forks);
	return (0);
}
