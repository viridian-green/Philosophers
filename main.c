/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/02 15:07:34 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// is_dead


void *routine(void *data)
{
	t_philo *philo;
	int is_dead;
	is_dead = 0;
	philo = (t_philo *)data;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo, 1);
	while (!is_dead)
	{

	}
	return (NULL);
}

int threading_philos(t_data *data, t_philo *philo)
{
	int i = 0;
	while (i < data->total_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, philo))
			return (exit_error("Thread failed to return\n"));
		i++;
	}
	return (1);
}

int parse_args(t_data *data, int argc, char **argv)
{
	// if (argc == 4)
	// {
	data->total_philo = 3;
	data->time_die = 800;
	data->time_eat = 200;
	data->time_sleep = 200;
	return (0);
	// }
	// else
	// 	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;

	if (parse_args(&data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	// struct timeval current_time;
	// gettimeofday(&current_time, NULL);
	philo =  malloc(sizeof(t_philo) * data.total_philo);
	if (!philo)
		return (1);
	data_init(&data, philo, argv);
	threading_philos(&data, philo);
}