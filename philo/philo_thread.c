/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:47:43 by timanish          #+#    #+#             */
/*   Updated: 2024/12/28 17:34:34 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(pthread_mutex_t **forks, int p_all)
{
	int	i;

	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p_all);
	i = 0;
	while (i < p_all)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i ++;
	}
}

void	init_philosopher_data(t_philo **p_data, char **argv,
			pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		(*p_data)[i].num = ft_atoi(argv[1]);
		(*p_data)[i].id = i + 1;
		(*p_data)[i].start_time = get_time();
		(*p_data)[i].die_time = ft_atoi(argv[2]);
		(*p_data)[i].eat_time = ft_atoi(argv[3]);
		(*p_data)[i].sleep_time = ft_atoi(argv[4]);
		if (argv[5])
			(*p_data)[i].must_eat = ft_atoi(argv[5]);
		else
			(*p_data)[i].must_eat = NONE;
		(*p_data)[i].left_forks = &forks[i];
		// (*p_data)[i].right_forks = &forks[(i + 1) % ft_atoi(argv[1])];
		if (i == 0)
			(*p_data)[i].right_forks = &forks[ft_atoi(argv[1]) - 1];
		else
			(*p_data)[i].right_forks = &forks[i - 1];
		(*p_data)[i].last_eat_time = get_time();
		(*p_data)[i].status = 0;
		(*p_data)[i].print_mutex = print_mutex;
		pthread_mutex_init(&(*p_data)[i].status_mutex, NULL);
		i ++;
	}
}

int	init_philosophers(t_philo **p_data, int argc, char **argv,
			pthread_mutex_t **forks)
{
	int				p_all;
	pthread_mutex_t	*print_mutex;

	print_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print_mutex, NULL);
	if (argc < 5)
	{
		printf("argment error\n");
		return (1);
	}
	p_all = ft_atoi(argv[1]);
	*p_data = (t_philo *)malloc(sizeof(t_philo) * p_all);
	init_forks(forks, p_all);
	init_philosopher_data(p_data, argv, *forks, print_mutex);
	return (0);
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
