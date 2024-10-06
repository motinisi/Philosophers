/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:59:51 by timanish          #+#    #+#             */
/*   Updated: 2024/10/06 19:24:15 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// typedef struct s_philo
// {
// 	int				id;
// 	int				state;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// }	t_philo;


void	philo_state(void *arg)
{

}

int	main(int argc, char **argv)
{
	int				total_p;
	t_philo			*p_num;
	pthread_t		*p_pthread;
	pthread_mutex_t	*p_mutex;
	int				i;

	total_p = argv[1];
	p_num = (t_philo *)malloc(sizeof(t_philo) * total_p);
	p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * total_p);
	p_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * total_p);
	i = 0;
	
	
	
	return (0);
}
