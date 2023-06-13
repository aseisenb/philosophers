#include "../include/philo.h"

void	ft_died(t_data *data)
{
	pthread_mutex_lock(&data->mutex[DIED]);
	data->dies = TRUE;
	pthread_mutex_unlock(&data->mutex[DIED]);
}

int	ft_check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[DIED]);
	if (philo->data->dies)
	{
		pthread_mutex_unlock(&philo->data->mutex[DIED]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mutex[DIED]);
	return (FALSE);
}

void	ft_done(t_data *data)
{
	pthread_mutex_lock(&data->mutex[DONE]);
	data->done = TRUE;
	pthread_mutex_unlock(&data->mutex[DONE]);
}

int	ft_check_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[DONE]);
	if (philo->data->done)
	{
		pthread_mutex_unlock(&philo->data->mutex[DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mutex[DONE]);
	return (FALSE);
}

void	ft_print(t_philo *philo, char const *const a)
{
	pthread_mutex_lock(&philo->data->mutex[PRINT]);
	if (*a == 'd' || (!ft_check_died(philo) && !ft_check_done(philo)))
		printf("%lu %d %s\n", relative_time(philo->data->simbegin), philo->id, a);
	pthread_mutex_unlock(&philo->data->mutex[PRINT]);
}