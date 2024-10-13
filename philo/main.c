/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:32:22 by timanish          #+#    #+#             */
/*   Updated: 2024/10/13 19:40:10 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// typedef struct s_philo
// {
// 	int				id;
// 	int				state;
// 	int				die_time;
// 	int				eat_time;
// 	int				sleep_time;
// 	int				fin_eat_time;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// }	t_philo;

// void	philo_state(void *arg)
// {

// }

int	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return (time);
}

int	main(int argc, char **argv)
{
	int				total_p;
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*fork;
	size_t			i;

	total_p = ft_atoi(argv[1]);
	p_data = (t_philo *)malloc(sizeof(t_philo) * total_p);
	p_data->eat_time = ft_atoi(argv[3]);
	p_data->sleep_time = ft_atoi(argv[4]);

	
}
