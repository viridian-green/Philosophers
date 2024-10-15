/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/15 15:28:06 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!is_dead(philo))
	{
		if (is_dead(philo))
			return (0);
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}


//MOve my start time
int threading_philos(t_data *data)
{
	int i = 0;

	// data->start_time = get_time();
	while (i < data->total_philo)
	{
	if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]))
	{
		return exit_error("Thread creation failed\n");
	}
	i++;
	}
	i = 0;
 	while (i < data->total_philo)
 	{
		pthread_join(data->p[i].thread, NULL);
		i++;
	}
	return (1);
}

int parse_args(t_data *data, int argc, char **argv)
{
	// if (argc == 4)
	// {
	data->total_philo = 12;
	data->time_die = 200;
	data->time_eat = 200;
	data->time_sleep = 200;
	return (0);
	// }
	// else
	// 	return (1);
}

int main(int argc, char **argv)
{
	//make a monitor in a thread
	t_data *data;
	int i = 0;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return exit_error("Error allocating memory for data\n");
	if (parse_args(data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	data_init(data, argv);
	threading_philos(data);
	destroy_mutex(data);
	free(data);
}