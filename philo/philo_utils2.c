/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:53:15 by timanish          #+#    #+#             */
/*   Updated: 2024/12/28 18:00:36 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_philo *p_data)
{
	if (p_data->num == 3)
	{
		if (pick_up_forks_when_three_philo(p_data))
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

int	pick_up_forks_when_three_philo(t_philo *p_data)
{
	pthread_mutex_lock(p_data->right_forks);
	if (print_messege("has taken a fork\n", p_data))
		return (1);
	pthread_mutex_lock(p_data->left_forks);
	if (print_messege("has taken a fork\n", p_data))
		return (1);
	return (0);
}
