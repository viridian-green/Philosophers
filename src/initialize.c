/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/25 15:01:29 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	long global_start_time;

	global_start_time = get_time();
	data->p =  malloc(sizeof(t_philo) * data->total_philo);
	if (!data->p )
		return (exit_error("Failed to allocate memory for philosophers."));
	while (i < data->total_philo)
	{
		data->p[i].id = i + 1;
		if (data->p[i].id % 2 == 0)
			data->p[i].is_even = 1;
		data->p[i].data = data;
		data->p[i].last_meal = global_start_time;
		data->p[i].is_eating = 0;
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
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
        perror("Writelock mutex initialization failed");
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
        perror("Data mutex initialization failed");
	return (0);
}