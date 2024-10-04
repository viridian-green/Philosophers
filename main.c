/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/04 12:53:12 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_data *data)
{
	//printf("hey");
	int is_dead;
	is_dead = 0;

	printf("Trying to lock mutex...\n");  // Test print
    pthread_mutex_lock(&data->write_mutex);
	//printf("Thread %ld locked mutex\n", pthread_self());
    printf("Locked mutex and printing: hey\n");  // Test print
    pthread_mutex_unlock(&data->write_mutex);
    printf("Unlocked mutex\n");  // Test print

    usleep(30);
	return 0;
}

	// while (!is_dead)
	// {

	// 	pthread_mutex_lock(p->data->write_mutex);
	// 	message("has taken a fork", p);
	// 	pthread_mutex_unlock(p->data->write_mutex);
	// 	is_dead = 1;
/*
	pthread_mutex_lock(&p->data->write_mutex);
	printf("hey");
	pthread_mutex_unlock(&p->data->write_mutex);
	pthread_mutex_lock(&p->data->write_mutex);
    message("is eating", p);
    pthread_mutex_unlock(&p->data->write_mutex);
	*/
	// }

void *routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo, 1);
	int ret = pthread_mutex_lock(&data->write_mutex);
	if (ret != 0)
    	printf("Error: failed to lock mutex, error code: %d\n", ret);

    pthread_mutex_unlock(&data->write_mutex);
	return (NULL);
}
//TODO : check if the casting is well done
int threading_philos(t_data *data)
{
	int i = 0;
	/*
	while (i < data->total_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
			return (exit_error("Thread failed to return\n"));
		i++;
	}
	*/
	for (int i = 0; i < data->total_philo; i++) {
    if (pthread_create(&data->p[i].thread, NULL, routine, data))
	{
        return exit_error("Thread creation failed\n");
    }
}

for (int i = 0; i < data->total_philo; i++) {
    pthread_join(data->p[i].thread, NULL);  // Join all threads
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
	t_data *data;
	data = malloc(sizeof(t_data));

	if (data == NULL) {
        return exit_error("Error allocating memory for data\n");
    }
	if (parse_args(data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	data_init(data, argv);
	threading_philos(data);
}