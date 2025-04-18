/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:58:09 by timanish          #+#    #+#             */
/*   Updated: 2025/04/09 16:47:08 by timanish         ###   ########.fr       */
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

# ifndef EAT
#  define EAT 2
# endif

# ifndef SLEEP
#  define SLEEP 3
# endif

# ifndef THINK
#  define THINK 4
# endif

# ifndef FIN
#  define FIN 5
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
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	*print_mutex;
}	t_philo;

long			ft_atoi(const char *str);
long long		get_time(void);
int				print_messege(char *messege, t_philo *p_data);
void			pick_up_forks(t_philo *p_data);
int				pickup_forks_for_edge_cases(t_philo *p_data);
void			philo_eat(t_philo *p_data);
void			philo_sleep(t_philo *p_data);
void			philo_think(t_philo *p_data);
void			*philo_routine(void *data);
int				check_death(t_philo *p_data, int p_num);
int				check_all_eaten(t_philo *p_data);
void			monitoring_philo(t_philo *p_data);
int				init_philosophers(t_philo **p_data, char **argv,
					pthread_mutex_t **forks);
void			create_philosopher_threads(pthread_t **p_pthread,
					t_philo *p_data);
void			join_philosopher_threads(pthread_t *p_pthread, t_philo *p_data);
void			cleanup(pthread_t *p_pthread,
					pthread_mutex_t *forks, t_philo *p_data);
int				argment_check(char **argv, int argc);
int				status_check(t_philo *p_data);
void			stay_philo_even(t_philo *p_data);
int				one_philo_logic(t_philo *p_data);
void			stay_philo(t_philo *p_data);

#endif