/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:43:44 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/01 18:34:50 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *eating(void *data)
{
	int i;
	i = 0;
	t_data *d = (t_data *)data;
	while (i < data->time_eat)
	{
		pthread_mutex_lock(&data->l_f);
		i++;
	}
	pthread_mutex_unlock(&data->l_f);
	return (NULL);
}

void start_routine(t_philo *philo)
{
	pthread_create(&philo->thread, NULL, eating, philo);
}

int main(int arc, char **argv)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	int i = 0;
	t_data data;
	t_philo philo;
	data_init(&data, &philo, argv);
	start_routine(&philo);
}