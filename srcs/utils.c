#include "../include/philo.h"

long	ft_atoi(char const *str)
{
	long	sign;
	long	nb;

	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

int	take_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	take_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
