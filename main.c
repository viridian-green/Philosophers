/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/15 13:11:37 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_dead(t_philo *p)
{
	if (get_time() - p->last_meal >= p->data->time_die)
	{
		message("has died", p);
		return (1);
	}
	return 0;
}

int is_eating(t_philo *p)
{
	int i = 0;
	if (p->id % 2 == 0)
	{
    	pthread_mutex_lock(p->l_f);
		message("has taken the left fork", p);
    	pthread_mutex_lock(p->r_f);
		message("has taken the right fork", p);
	} else
	{
		pthread_mutex_lock(p->r_f);
		message("has taken the right fork", p);
		pthread_mutex_lock(p->l_f);
		message("has taken the left fork", p);
	}
	message("is eating", p);
	pthread_mutex_unlock(&p->data->meal_lock);
	p->last_meal = get_time();
	pthread_mutex_lock(&p->data->meal_lock);
	ft_usleep(p->data->time_eat);
	pthread_mutex_unlock(p->r_f);
	pthread_mutex_unlock(p->l_f);
	return 0;
}

int is_sleeping(t_philo *p)
{
	message("is sleeping", p);
	ft_usleep(p->data->time_sleep);
	return (0);
}

int is_thinking(t_philo *p)
{
	message("is thinking", p);
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!is_dead(philo))
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

int threading_philos(t_data *data)
{
	int i = 0;

	data->start_time = get_time();
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
	data->total_philo = 100;
	data->time_die = 800;
	data->time_eat = 200;
	data->time_sleep = 200;
	return (0);
	// }
	// else
	// 	return (1);
}

void destroy_mutex(t_data *data)
{
	int i = 0;
	while (i < data->total_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->meal_lock);

}

int main(int argc, char **argv)
{
	//make a monitor in a thread
	t_data *data;
	int i = 0;
	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
        return exit_error("Error allocating memory for data\n");
    }
	if (parse_args(data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	data_init(data, argv);
	 threading_philos(data);
	//printf("%ld", get_time());
	destroy_mutex(data);
}