/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisi <nisi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:01:58 by timanish          #+#    #+#             */
/*   Updated: 2025/04/01 16:53:43 by nisi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*forks;
	pthread_t		monitoring_thread;

	if (argment_check(argv, argc))
		return (0);
	init_philosophers(&p_data, argv, &forks);
	create_philosopher_threads(&p_pthread, p_data);
	pthread_create(&monitoring_thread, NULL, (void *)monitoring_philo, p_data);
	join_philosopher_threads(p_pthread, p_data);
	pthread_join(monitoring_thread, NULL);
	cleanup(p_pthread, forks, p_data);
	return (0);
}
