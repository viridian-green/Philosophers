
#include "header.h"

//function that creates a fork/mutex for each philo
void	create_fork(t_philo *p)
{
	int i = 0;
	while (i < p->arg->n_philo)
	{
		p->r_f = //create->mutex;
		i++;
	}
}

int main()
{
	int i = 0;
	t_arg arg;
	t_philo p;
	while (i < arg.n_philo)
	{
		p.id = i;
		i++;
	}
	sleep(6);
}