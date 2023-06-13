#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

typedef enum e_mutexes
{
	PRINT,
	FOOD,
	DONE,
	DIED,
	M_NUM
}	t_mutexes;

typedef struct s_data
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat;
	unsigned long	simbegin;
	int				done;
	int				dies;
	pthread_mutex_t	*mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	last_meal;
	int				meal_counter;
	int				lfork;
	int				rfork;
	pthread_mutex_t	*fork;
	t_data			*data;
}	t_philo;

long			ft_atoi(char const *str);
int				take_max(int a, int b);
int				take_min(int a, int b);
int				ft_valid_args(int ac, char const *const *av);
unsigned long	current_time(void);
unsigned long	relative_time(unsigned long begin);
void			time_delay(unsigned long msec);
void			ft_print(t_philo *philo, char const *const a);
void			ft_died(t_data *data);
void			ft_done(t_data *data);
int				ft_check_died(t_philo *philo);
int				ft_check_done(t_philo *philo);
int				ft_simulator(t_philo *philo, t_data *data);
void			*philo_routine(void *arg);
int				ft_init_philo(t_philo **philo, t_data *data);
int				ft_init_data_mutexes(t_data **data);
int				ft_init_data(t_data **data, int ac, char const *const *av);
int				ft_init(t_philo **philo, t_data **data,
					int ac, char const *const *av);

#endif