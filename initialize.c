/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/01 13:42:57 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void init_forks(t_philo *philos, t_arg *args)
{
	int i = 0;
	while (i < args->n_philo)
	{
		if (pthread_mutex_init(&philos[i].l_f, NULL))
			return ;
		i++;
	}
}

//Function that initializes a fork/mutex for each philosopher (on the left).
//
void	init_philos(t_philo *philos, t_arg *args)
{
	int i = 0;
	while (i < args->n_philo)
	{
		philos[i].id = i + 1;
		//data->r_f = 1;//create->mutex;
		i++;
	}
}

void data_init(t_arg *args, t_philo *philos, char **argv)
{
	//arg->n_philo = ft_atoi(argv[0]);
	args->n_philo = 3;
	args->time_die = 2;
	args->time_eat = 3;
	args->time_sleep = 4;
	init_philos(philos, args);
	init_forks(philos, args);

}