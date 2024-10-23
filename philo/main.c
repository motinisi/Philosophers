#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return (time);
}

int	print_messege(char *messege, t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->status == DIE)
		return (1);
	else
		printf("%lld %d %s", get_time() - base, p_data->id, messege);
	return (0);
}

void	pick_up_forks(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->id % 2 == 0)
	{
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork left\n", p_data))
			return ;
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork right\n", p_data))
			return ;
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(p_data->right_forks);
		if (print_messege("has taken a fork right\n", p_data))
			return ;
		pthread_mutex_lock(p_data->left_forks);
		if (print_messege("has taken a fork left\n", p_data))
			return ;
	}
}

void	eat(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	p_data->last_eat_time = get_time() - base;
	if (p_data->status == DIE)
		return ;
	else
		printf("%lld %d is eating\n", p_data->last_eat_time, p_data->id);
	usleep(1000 * p_data->eat_time);
	pthread_mutex_unlock(p_data->left_forks);
	pthread_mutex_unlock(p_data->right_forks);
	p_data->eat_count++;
}

void	go_to_sleep(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;
	if (p_data->status == DIE || p_data->eat_count == p_data->must_eat)
		return ;
	else
		printf("%lld %d is sleeping\n", get_time() - base, p_data->id);
	usleep(1000 * p_data->sleep_time);
}

void	think(t_philo *p_data)
{
	long long	base;

	base = p_data->start_time;

	if (p_data->status == DIE)
		return ;
	else
		printf("%lld %d is thinking\n", get_time() - base, p_data->id);
}

void	*philo_routine(void *data)
{
	t_philo		*p_data;
	long long	base;

	p_data = (t_philo *)data;
	base = p_data->start_time;
	p_data->eat_count = 0;
	while (1)
	{
		pick_up_forks(p_data);
		if (p_data->status == DIE)
			return (0);
		eat(p_data);
		if (p_data->status == DIE || p_data->eat_count == p_data->must_eat)
			return (0);
		go_to_sleep(p_data);
		if (p_data->status == DIE)
			return (0);
		think(p_data);
	}
	return (0);
}

int	check_death(t_philo *p_data)
{
	long long	present_time;
	int			p_num;
	int			i;
	int			tmp;

	p_num = p_data[0].num;
	i = 0;
	while (i < p_num)
	{
		present_time = get_time() - p_data[i].start_time;
		if (present_time - p_data[i].last_eat_time > p_data[i].die_time)
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
		if (check_death(p_data))
			return ;
		if (check_all_eaten(p_data))
			return ;
		usleep(1000);
	}
}

void	init_philosophers(t_philo **p_data, int argc, char **argv, pthread_mutex_t **forks)
{
	int	p_all;
	int	i;

	if (argc < 5)
	{
		printf("argment error\n");
		return ;
	}
	p_all = atoi(argv[1]);
	*p_data = (t_philo *)malloc(sizeof(t_philo) * p_all);
	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p_all);
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
		pthread_mutex_init(&(*forks)[i], NULL);
		(*p_data)[i].left_forks = &(*forks)[i];
		(*p_data)[i].right_forks = &(*forks)[(i + 1) % p_all];
		(*p_data)[i].last_eat_time = get_time();
		(*p_data)[i].status = 0;
		i++;
	}
}

void	create_philosopher_threads(pthread_t **p_pthread, t_philo *p_data)
{
	int	p_all;
	int	i;

	p_all = p_data[0].num;
	*p_pthread = (pthread_t *)malloc(sizeof(pthread_t) * p_all);
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

void	cleanup(pthread_t *p_pthread, pthread_mutex_t *forks, t_philo *p_data)
{
	int	p_all;
	int	i;

	p_all = p_data[0].num;
	i = 0;
	while (i < p_all)
	{
		pthread_mutex_destroy(&forks[i]);
		i ++;
	}
	free(p_pthread);
	free(forks);
	free(p_data);
}

int	main(int argc, char **argv)
{
	t_philo			*p_data;
	pthread_t		*p_pthread;
	pthread_mutex_t	*forks;
	pthread_t		monitoring_thread;

	init_philosophers(&p_data, argc, argv, &forks);
	create_philosopher_threads(&p_pthread, p_data);
	pthread_create(&monitoring_thread, NULL, (void *)monitoring_philo, p_data);
	join_philosopher_threads(p_pthread, p_data);
	pthread_join(monitoring_thread, NULL);
	cleanup(p_pthread, forks, p_data);
	return (0);
}