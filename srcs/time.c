#include "../include/philo.h"

unsigned long	current_time(void)
{
	struct timeval	time;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday (&time, NULL) == -1)
		write (2, "Error: GETTIMEOFDAY(2)\n", 23);
	s = time.tv_sec * 1000;
	u = time.tv_usec / 1000;
	return (s + u);
}

unsigned long	relative_time(unsigned long begin)
{
	unsigned long	abs_time;

	abs_time = current_time ();
	return (abs_time - begin);
}

void	time_delay(unsigned long msec)
{
	unsigned long	cur;

	cur = current_time();
	while (current_time() - cur < msec)
		usleep(10);
}
