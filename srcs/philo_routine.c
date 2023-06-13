#include "../include/philo.h"

static int	ft_start_eating(t_philo *self)
{
	pthread_mutex_lock(&self->fork[take_min(self->lfork, self->rfork)]);
	ft_print(self, "has taken a fork");
	if (self->lfork == self->rfork)
	{
		pthread_mutex_unlock(&self->fork[take_min(self->lfork, self->rfork)]);
		return (FAILURE);
	}
	pthread_mutex_lock(&self->fork[take_max(self->lfork, self->rfork)]);
	ft_print(self, "has taken a fork");
	ft_print(self, "is eating");
	return (SUCCESS);
}

static int	ft_finish_eating(t_philo *self)
{
	ft_print(self, "is sleeping");
	pthread_mutex_unlock(&self->fork[take_max(self->lfork, self->rfork)]);
	pthread_mutex_unlock(&self->fork[take_min(self->lfork, self->rfork)]);
	time_delay(self->data->time_to_sleep);
	return (SUCCESS);
}

static int	ft_eating(t_philo *self)
{
	if (ft_start_eating(self) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&self->data->mutex[FOOD]);
	self->last_meal = current_time();
	self->meal_counter++;
	pthread_mutex_unlock(&self->data->mutex[FOOD]);
	if (ft_check_done(self))
	{
		ft_finish_eating(self);
		return (FAILURE);
	}
	time_delay(self->data->time_to_eat);
	ft_finish_eating(self);
	return (SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	if (self->id % 2 == 0)
	{
		ft_print(self, "is thinking");
		time_delay(self->data->time_to_eat);
	}
	while (1)
	{
		if (ft_check_died(self))
			break ;
		if (ft_eating(self) != SUCCESS)
			break ;
		ft_print(self, "is thinking");
		time_delay(self->data->time_to_think);
	}
	return (NULL);
}
