/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/02 12:17:21 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(t_philo *philos, t_data *data)
{
	int i = 0;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->total_philo);
	if (!data->fork)
		{
		perror("error");
		EXIT_FAILURE;
	}
	while (i < data->total_philo)
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
	philo =  malloc(sizeof(t_philo) * data->total_philo);
	while (i < data->total_philo)
	{
		philo[i].id = i + 1;
		philo[i].l_f = &data->fork[i];
		philo[i].r_f = &data->fork[(i + 1) % data->total_philo];
		i++;
	}
}

void data_init(t_data *data, t_philo *philos, char **argv)
{
	data->total_philo = 3;
	data->time_die = 800;
	data->time_eat = 200;
	data->time_sleep = 200;
	init_forks(philos, data);
	init_philos(philos, data);
}