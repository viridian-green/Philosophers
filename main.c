/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/03 19:21:54 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_philo *p)
{
	int is_dead;
	is_dead = 0;
	pthread_mutex_init(p->data->write_mutex, NULL);
	pthread_mutex_lock(p->data->write_mutex);
	printf("hey");
	pthread_mutex_unlock(p->data->write_mutex);

	pthread_mutex_lock(p->data->write_mutex);
    message("is eating", p);
    pthread_mutex_unlock(p->data->write_mutex);

    ft_usleep(p, p->data->time_eat);
	return 0;
}

	// while (!is_dead)
	// {
	// 	pthread_mutex_lock(p->data->write_mutex);
	// 	message("has taken a fork", p);
	// 	pthread_mutex_unlock(p->data->write_mutex);
	// 	is_dead = 1;
	// }

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo, 1);
	eat(philo);
	return (NULL);
}
//TODO : check if the casting is well done
int threading_philos(t_data *data, t_philo *philo)
{
	int i = 0;
	while (i < data->total_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
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