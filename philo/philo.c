#include "philo.h"

void	init_arg(t_philo_info *pi, char **av)
{
	pi->philo_size = ft_atoi(av[1]);
	pi->die_time = ft_atoi(av[2]);
	pi->eat_time = ft_atoi(av[3]);
	pi->sleep_time = ft_atoi(av[4]);
	if (av[5])
		pi->eat_limit = ft_atoi(av[5]);
	else
		pi->eat_limit = -1;
	pi->eat_count = 0;
	pi->philos = malloc(sizeof(t_philo) * pi->philo_size);
	pi->forks = malloc(sizeof(pthread_mutex_t) * pi->philo_size);
	gettimeofday(&pi->tv, NULL);
	pi->start_ms = (pi->tv.tv_usec / 1000 + pi->tv.tv_sec * 1000);
}

void	init_thread(t_philo_info *pi)
{
	int	i;

	i = -1;
	pthread_mutex_init(&pi->dead_mutex, NULL);
	pthread_mutex_init(&pi->check_mutex, NULL);
	while (++i < pi->philo_size)
		pthread_mutex_init(&pi->forks[i], NULL);
	i = -1;
	while (++i < pi->philo_size)
	{
		pi->philos[i].pi = pi;
		pi->philos[i].last_eat_time = get_ms(pi);
		pi->philos[i].index = i;
		if (pthread_create(&pi->philos[i].thread, NULL, philo_loop,
				&pi->philos[i]) != 0)
			printf("Error.\n");
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	t_philo_info	*pi;

	if ((ac != 5 && ac != 6) || arg_check(av + 1) == -1)
	{
		printf("Arg Error.\n");
		return (1);
	}
	pi = malloc(sizeof(t_philo_info));
	init_arg(pi, av);
	init_thread(pi);
	monitor(pi);
	return (0);
}
