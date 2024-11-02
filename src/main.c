/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/11/02 14:31:04 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	threading_philos(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->total_philo)
	{
		if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]))
			return (exit_error("Error. Failed to create thread\n", data));
		i++;
	}
	monitoring(data);
	i = 0;
	while (i < data->total_philo)
	{
		if (pthread_join(data->p[i].thread, NULL))
			return (exit_error("Error. Failed to create thread\n", data));
		i++;
	}
	return (1);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	data->total_philo = ft_atoi(argv[1], data);
	data->time_die = ft_atoi(argv[2], data);
	data->time_eat = ft_atoi(argv[3], data);
	data->time_sleep = ft_atoi(argv[4], data);
	data->stop_simulation = 0;
	if (argc == 6)
		data->total_meals = ft_atoi(argv[5], data);
	else
		data->total_meals = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (exit_error("Error allocating memory for data\n", data));
	if (parse_args(data, argc, argv))
		return (exit_error("Error. Invalid arguments\n", data));
	if (data_init(data, argv))
		return (exit_error("Error initializing data\n", data));
	if (!threading_philos(data))
		return (EXIT_FAILURE);
	destroy_mutex(data);
	free_all(data);
}
