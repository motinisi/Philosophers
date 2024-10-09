/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:59:51 by timanish          #+#    #+#             */
/*   Updated: 2024/10/09 18:17:55 by timanish         ###   ########.fr       */
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



void	philo_state(void *arg)
{

}

void	philo_routine(void *arg)
{
	t_philo	*p_data;

	p_data = (t_philo *)arg;

	while(1)
	{
		printf("%d %d is eating\n", )
		usleep(1000 * p_data->eat_time);
	}
}

int	main(int argc, char **argv)
{
	int				total_p;
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*fork;
	int				i;

	total_p = argv[1];
	p_data = (t_philo *)malloc(sizeof(t_philo) * total_p);
	p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * total_p);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_p);
	i = 0;



	return (0);
}
