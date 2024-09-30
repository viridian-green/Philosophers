/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/09/30 13:09:58 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void data_init(t_arg *arg, t_philo *philo, char **argv)
{
	//arg->n_philo = argv[0];
	if (pthread_mutex_init(&philo->l_f, NULL))
		return ;
	arg->n_philo = 3;
	arg->time_die = argv[1];
	arg->time_eat = argv[2];
	arg->time_sleep = argv[3];

}

//function that creates a fork/mutex for each philo
void	init_philos(t_philo *p)
{
	int i = 0;
	while (i < p->arg->n_philo)
	{
		p[i].id = i;
		if (pthread_mutex_init(&p[i].l_f, NULL))
			return ;
		p->l_f = 1;//create->mutex;
		i++;
	}
}

int main(int arc, char **argv)
{
	int i = 0;
	t_arg args;
	t_philo philo;

	data_init(&args, &philo, argv);
	while (i < args.n_philo)
	{
		philo.id = i;
		i++;
	}
	pthread_create(&philo, NULL, init_philos, NULL);
	sleep(6);
}