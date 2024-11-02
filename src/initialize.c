/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/11/02 14:23:36 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//Function that initializes all forks.
int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->total_philo);
	if (!data->fork)
		return (exit_error("Failed to allocate memory for forks.", data));
	while (i < data->total_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (exit_error("Failed to initialize mutex.", data));
		i++;
	}
	return (1);
}

//Function that initializes the data for each philosopher
int	init_philos(t_data *data)
{
	int		i;
	long	global_start_time;

	i = 0;
	global_start_time = get_time();
	data->p = malloc(sizeof(t_philo) * data->total_philo);
	if (!data->p)
		return (exit_error("Failed to allocate memory for philosophers."\
			, data));
	while (i < data->total_philo)
	{
		data->p[i].id = i + 1;
		if (data->p[i].id % 2 == 0)
			data->p[i].is_even = 1;
		data->p[i].data = data;
		data->p[i].last_meal = get_time();
		data->p[i].is_eating = 0;
		data->p[i].is_dead = 0;
		data->p[i].l_f = &data->fork[i];
		data->p[i].r_f = &data->fork[(i + 1) % data->total_philo];
		i++;
	}
	return (1);
}

int	data_init(t_data *data, char **argv)
{
	if (!init_forks(data) || !init_philos(data))
		return (1);
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		exit_error("Writelock mutex initialization failed", data);
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		exit_error("Data mutex initialization failed", data);
	return (0);
}
