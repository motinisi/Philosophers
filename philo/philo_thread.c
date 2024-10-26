/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:47:43 by timanish          #+#    #+#             */
/*   Updated: 2024/10/26 19:32:22 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t **forks, int p_all)
{
	size_t	i;

	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p_all);
	i = 0;
	while (i < p_all)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i ++;
	}
}

void	init_philosopher_data(t_philo **p_data, int p_all, char **argv,
			pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < p_all)
	{
		(*p_data)[i].num = p_all;
		(*p_data)[i].id = i + 1;
		(*p_data)[i].start_time = get_time();
		(*p_data)[i].die_time = atoi(argv[2]);
		(*p_data)[i].eat_time = atoi(argv[3]);
		(*p_data)[i].sleep_time = atoi(argv[4]);
		if (argv[5])
			(*p_data)[i].must_eat = atoi(argv[5]);
		else
			(*p_data)[i].must_eat = NONE;
		(*p_data)[i].left_forks = &forks[i];
		(*p_data)[i].right_forks = &forks[(i + 1) % p_all];
		(*p_data)[i].last_eat_time = get_time();
		(*p_data)[i].status = 0;
		if (i != 0)
			(*p_data)[i].prev = &(*p_data)[i - 1];
		i ++;
	}
}

void	init_philosophers(t_philo **p_data, int argc, char **argv,
			pthread_mutex_t **forks)
{
	int	p_all;

	if (argc < 5)
	{
		printf("argment error\n");
		return ;
	}
	p_all = atoi(argv[1]);
	*p_data = (t_philo *)malloc(sizeof(t_philo) * p_all);
	init_forks(forks, p_all);
	init_philosopher_data(p_data, p_all, argv, *forks);
}

void	create_philosopher_threads(pthread_t **p_pthread, t_philo *p_data)
{
	int	p_all;
	int	i;

	p_all = p_data[0].num;
	*p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * p_all);
	if (!*p_pthread)
		return ;
	i = 0;
	while (i < p_all)
	{
		pthread_create(&(*p_pthread)[i], NULL, philo_routine, &p_data[i]);
		usleep(100);
		i++;
	}
}

void	join_philosopher_threads(pthread_t *p_pthread, t_philo *p_data)
{
	int	p_all;
	int	i;

	p_all = p_data[0].num;
	i = 0;
	while (i < p_all)
	{
		pthread_join(p_pthread[i], NULL);
		i++;
	}
}
