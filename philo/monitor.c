/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:06:11 by timanish          #+#    #+#             */
/*   Updated: 2024/12/15 19:25:10 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *p_data, int p_num)
{
	long long	present_time;
	int			i;
	int			tmp;

	i = 0;
	while (i < p_num)
	{
		pthread_mutex_lock(&p_data[i].status_mutex);
		present_time = get_time() - p_data[i].start_time;
		if (present_time - p_data[i].last_eat_time > p_data[i].die_time
			&& p_data->status != FIN)
		{
			p_data[i].status = DIE;
			tmp = i;
			i = -1;
			while (++i < p_num)
				p_data[i].status = DIE;
			printf("%lld %d died\n", present_time, p_data[tmp].id);
			// print_messege("died\n", &p_data[tmp]);
			pthread_mutex_unlock(&p_data[tmp].status_mutex);
			return (1);
		}
		pthread_mutex_unlock(&p_data[i].status_mutex);
		i++;
	}
	return (0);
}

int	check_all_eaten(t_philo *p_data)
{
	int	p_num;
	int	i;
	int	fin_eat_num;

	pthread_mutex_lock(&p_data->status_mutex);
	p_num = p_data[0].num;
	pthread_mutex_unlock(&p_data->status_mutex);
	i = 0;
	fin_eat_num = 0;
	while (i < p_num)
	{
		pthread_mutex_lock(&p_data[i].status_mutex);
		if (p_data[i].eat_count == p_data[i].must_eat)
			fin_eat_num++;
		pthread_mutex_unlock(&p_data[i].status_mutex);
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
		if (check_death(p_data, p_data->num))
			return ;
		if (check_all_eaten(p_data))
			return ;
		usleep(1000);
	}
}
