#include "../include/philo.h"

static void	ft_destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy(&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy(&data->mutex[i++]);
}

static int	ft_all_ate(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->must_eat == -1)
		return (FALSE);
	i = -1;
	done = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_lock(&philo->data->mutex[FOOD]);
		meals_count = philo[i].meal_counter;
		pthread_mutex_unlock(&philo->data->mutex[FOOD]);
		if (meals_count >= data->must_eat)
			if (++done == data->philo_nb - 1)
				return (TRUE);
		usleep (50);
	}
	return (FALSE);
}

static int	ft_observer(t_philo *philo, t_data *data)
{
	int				i;
	unsigned long	l_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex[FOOD]);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock(&data->mutex[FOOD]);
		if (l_meal && ft_all_ate(philo, data))
		{
			ft_done (data);
			break ;
		}
		if (l_meal && current_time() - l_meal > (unsigned long)data->time_to_die)
		{
			ft_died(data);
			ft_print(&philo[i], "died");
			break ;
		}
		i = (i + 1) % data->philo_nb;
		usleep (200);
	}
	return (SUCCESS);
}

int	ft_simulator(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*th;

	th = malloc(sizeof(pthread_t) * (size_t)data->philo_nb);
	if (th == NULL)
		return (FAILURE);
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_create(&th[i], 0, philo_routine, (void *)&philo[i]))
		{
			while (i--)
				pthread_join(th[i], NULL);
			return ((void)free(th), FAILURE);
		}
	}
	if (ft_observer(philo, data) != SUCCESS)
		return ((void)ft_destroy_mutexes(philo, data), (void)free(th),
			FAILURE);
	i = -1;
	while (++i < data->philo_nb)
		if (pthread_join(th[i], NULL))
			return (FAILURE);
	return ((void)ft_destroy_mutexes(philo, data), (void)free(th), SUCCESS);
}
