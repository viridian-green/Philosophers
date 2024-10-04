/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/04 12:40:22 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function that initializes all forks.
int init_forks(t_data *data)
{
	int i = 0;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->total_philo);
	if (!data->fork)
		{
		return (exit_error("Failed to allocate memory for forks."));
		EXIT_FAILURE;
	}
	while (i < data->total_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			return (exit_error("Failed to initialize mutex."));
			EXIT_FAILURE;
		}
		i++;
	}
	return (0);
}

//Function that initializes the data for each philosopher
int	init_philos(t_data *data)
{
	int i = 0;
	data->p =  malloc(sizeof(t_philo) * data->total_philo);
	if (!data->p )
		return (exit_error("Failed to allocate memory for philosophers."));
	while (i < data->total_philo)
	{
		data->p[i].id = i + 1;
		data->p[i].start_time = get_time();
		data->p[i].last_meal = get_time() - data->p->start_time;
		data->p[i].has_eaten = 0;
		data->p[i].is_dead = 0;
		data->p[i].l_f = &data->fork[i];
		data->p[i].r_f = &data->fork[(i + 1) % data->total_philo];
		i++;
	}
	return (0);
}

int data_init(t_data *data, char **argv)
{
	if (init_forks(data) || init_philos(data))
		return (-1);
	pthread_mutex_init(&data->write_mutex, NULL);
	return (0);
}