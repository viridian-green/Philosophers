/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/23 16:24:20 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void monitor_philos(t_data *data)
{
	pthread_t	monitor;
	pthread_create(&monitor, NULL, monitoring, (void *)data);
	pthread_join(monitor, NULL);
}

// TODO : create a mutex for the start time
int threading_philos(t_data *data)
{
	int i = 0;
	pthread_t	monitor;
	pthread_create(&monitor, NULL, monitoring, (void *)data);
	while (i < data->total_philo)
	{
	if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]))
	{
		return exit_error("Thread creation failed\n");
	}
	i++;
	}

//Monitor function here
 	while (i-- > 0)
		pthread_join(data->p[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (1);
}

// int threading_philos(t_data *data)
// {
// 	int i = 0;
// 	while (i < data->total_philo)
// 	{
// 	if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]))
// 	{
// 		return exit_error("Thread creation failed\n");
// 	}
// 	i++;
// 	}

// //Monitor function here
//  	while (i-- > 0)
// 		pthread_join(data->p[i].thread, NULL);
// 	return (1);
// }

int parse_args(t_data *data, int argc, char **argv)
{
    if (argc == 5 || argc == 6)
    {
    data->total_philo = ft_atoi(argv[1]);
    data->time_die = ft_atoi(argv[2]);
    data->time_eat = ft_atoi(argv[3]);
    data->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->total_meals = ft_atoi(argv[5]);
    return (0);
    }
    else
        return 1;
}

int main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return exit_error("Errong_philos(data);r allocating memory for data\n");
	if (parse_args(data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	data_init(data, argv);
	// monitor_philos(data);
	threading_philos(data);
	destroy_mutex(data);
	free_all(data);
}