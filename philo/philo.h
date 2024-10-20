/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:58:09 by timanish          #+#    #+#             */
/*   Updated: 2024/10/18 17:58:50 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# ifndef NONE
#  define NONE -1
# endif

# ifndef DIE
#  define DIE 1
# endif

# ifndef FIN
#  define FIN 2
# endif

typedef struct s_philo
{
	int				num;
	int				id;
	int				status;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	long long		start_time;
	long long		last_eat_time;
	int				must_eat;
	int				eat_count;
	pthread_mutex_t	*left_forks;
	pthread_mutex_t	*right_forks;
}	t_philo;

static size_t	ft_strlen_n(const char *str);
long			ft_atoi(const char *str);
#endif