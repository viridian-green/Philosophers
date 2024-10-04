/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/04 12:20:10 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function that initializes all forks.
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

//Function that initializes the data for each philosopher
void	init_philos(t_philo *philo, t_data *data)
{
	int i = 0;
	philo =  malloc(sizeof(t_philo) * data->total_philo);
	while (i < data->total_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].start_time = get_time();
		philo[i].last_meal = get_time() - philo->start_time;
		philo[i].has_eaten = 0;
		philo[i].is_dead = 0;
		philo[i].l_f = &data->fork[i];
		philo[i].r_f = &data->fork[(i + 1) % data->total_philo];
		i++;
	}
}

void data_init(t_data *data, t_philo *philos, char **argv)
{
	data->philos =  malloc(sizeof(t_philo) * data->total_philo);
	init_forks(philos, data);
	init_philos(philos, data);
	pthread_mutex_init(&data->write_mutex, NULL);
}