#include "philo.h"

void	monitor(t_philo_info *pi)
{
	int	i;

	i = 1;
	while (1)
	{
		pthread_mutex_lock(&pi->check_mutex);
		if (pi->eat_limit != -1 && pi->eat_count >= pi->eat_limit
			* pi->philo_size)
		{
			pthread_mutex_lock(&pi->dead_mutex);
			return ;
		}
		if (get_ms(pi) - pi->philos[i % pi->philo_size].last_eat_time
			>= pi->die_time)
		{
			pthread_mutex_lock(&pi->dead_mutex);
			printf("%lu %d died\n", get_ms(pi),
				(i % pi->philo_size) + 1);
			return ;
		}
		pthread_mutex_unlock(&pi->check_mutex);
		i++;
		usleep(100);
	}
}

int	arg_check(char **av)
{
	int	i;

	i = -1;
	if (ft_atoi(av[0]) == 0)
		return (-1);
	if (av[4] && ft_atoi(av[4]) == 0)
		return (-1);
	while (av[++i])
		if (ft_atoi(av[i]) == -1)
			return (-1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
		return (-1);
	return (res);
}
