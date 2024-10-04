/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/04 14:26:13 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int eat(t_data *data)
{
	int is_dead;
	is_dead = 0;
	int i = 0;
	while (!is_dead)
	{
    pthread_mutex_lock(&data->write_mutex);
	message("has taken a fork", data->p);
	pthread_mutex_unlock(&data->write_mutex);
	usleep(30);
	is_dead = 1;
	}
	return 0;
}

/*
pthread_mutex_lock(data->p->l_f);
pthread_mutex_lock(data->p->r_f);
pthread_mutex_unlock(data->p->l_f);
	pthread_mutex_unlock(data->p->l_f);
*/

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg; // Cast arg to t_philo pointer

    printf("%d\n", philo->id); // Access the philosopher's ID directly
    eat(philo->data);
	return (NULL);
}
//TODO : check if the casting is well done
int threading_philos(t_data *data)
{
	int i = 0;
	while (i < data->total_philo)
	{
    if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]))
	{
        return exit_error("Thread creation failed\n");
	}
	i++;
    }
 for (int i = 0; i < data->total_philo; i++)
 	{
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
	int i = 0;
	data = malloc(sizeof(t_data));
	if (data == NULL) {
        return exit_error("Error allocating memory for data\n");
    }
	if (parse_args(data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	data_init(data, argv);
	threading_philos(data);
}