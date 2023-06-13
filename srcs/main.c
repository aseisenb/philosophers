#include "../include/philo.h"

static int	ft_edgecases(int ac, char const *const *av)
{
	if ((ac == 6 && ft_atoi(av[5]) == 0))
		return (TRUE);
	if (ft_atoi(av[1]) == 0)
		return (TRUE);
	return (FALSE);
}

static void	ft_clear_memory(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free (data->mutex);
	if (data)
		free (data);
	if (philo && philo->fork)
		free (philo->fork);
	if (philo)
		free (philo);
}

int	main(int ac, char const *const *av)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (ft_valid_args(ac, av) != SUCCESS)
		return ((void)ft_clear_memory(philo, data), EXIT_FAILURE);
	if (ft_edgecases(ac, av))
		return ((void)ft_clear_memory(philo, data), EXIT_SUCCESS);
	if (ft_init(&philo, &data, ac, av) != SUCCESS)
		return ((void)ft_clear_memory(philo, data), EXIT_FAILURE);
	if (ft_simulator(philo, data) != SUCCESS)
		return ((void)ft_clear_memory(philo, data), EXIT_FAILURE);
	return ((void)ft_clear_memory(philo, data), EXIT_SUCCESS);
}
