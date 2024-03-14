#include "philo.h"

void	*philo_loop(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->pi->forks[p->index]);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(&p->pi->forks[(p->index + 1)
			% p->pi->philo_size]);
		print_status(p, "has taken a fork");
		print_status(p, "is eating");
		eat_status(p);
		ms_sleep(p, p->pi->eat_time);
		print_status(p, "is sleeping");
		pthread_mutex_unlock(&p->pi->forks[p->index]);
		pthread_mutex_unlock(&p->pi->forks[(p->index + 1)
			% p->pi->philo_size]);
		ms_sleep(p, p->pi->sleep_time);
		print_status(p, "is thinking");
	}
	return (NULL);
}

void	print_status(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->pi->dead_mutex);
	printf("%lu %d %s\n", get_ms(p->pi), p->index + 1, str);
	pthread_mutex_unlock(&p->pi->dead_mutex);
}

void	eat_status(t_philo *p)
{
	pthread_mutex_lock(&p->pi->check_mutex);
	p->pi->eat_count++;
	p->last_eat_time = get_ms(p->pi);
	pthread_mutex_unlock(&p->pi->check_mutex);
}

unsigned long	get_ms(t_philo_info *pi)
{
	gettimeofday(&pi->tv, NULL);
	return ((pi->tv.tv_usec / 1000 + pi->tv.tv_sec * 1000) - pi->start_ms);
}

void	ms_sleep(t_philo *p, int time)
{
	unsigned long	wakeup_time;

	wakeup_time = get_ms(p->pi) + time;
	while (get_ms(p->pi) < wakeup_time)
		usleep(100);
}
