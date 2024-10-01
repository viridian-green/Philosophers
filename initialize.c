/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/01 16:58:42 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(t_philo *philos, t_data *data)
{
	int i = 0;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		{
		perror("error");
		EXIT_FAILURE;
	}
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			perror("error");
			EXIT_FAILURE;
		}
		i++;
	}
}

//Function that initializes a fork/mutex for each philosopher (on the left).
void	init_philos(t_philo *philo, t_data *data)
{
	int i = 0;
	philo =  malloc(sizeof(t_philo) * data->n_philo);
	while (i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].l_f = &data->fork[i];
		philo[i].r_f = &data->fork[(i + 1) % data->n_philo];
		i++;
	}
}

void data_init(t_data *args, t_philo *philos, char **argv)
{
	//arg->n_philo = ft_atoi(argv[0]);
	args->n_philo = 3;
	args->time_die = 2;
	args->time_eat = 3;
	args->time_sleep = 4;
	init_forks(philos, args);
	init_philos(philos, args);
}