/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:06:11 by timanish          #+#    #+#             */
/*   Updated: 2024/10/26 19:08:16 by timanish         ###   ########.fr       */
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
		present_time = get_time() - p_data[i].start_time;
		if (present_time - p_data[i].last_eat_time > p_data[i].die_time
			&& p_data->status != FIN)
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
		if (check_death(p_data, p_data->num))
			return ;
		if (check_all_eaten(p_data))
			return ;
		usleep(1000);
	}
}