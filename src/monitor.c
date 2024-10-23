/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/23 16:54:13 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *monitoring(void *arg)
{
	t_data *data;
	usleep(1000);
	data = (t_data *)arg;
	while (1)
	{ // Avoid busy-waiting
		int i;
		i = 0;
		while (i < data->total_philo)
		{
			printf("looping monitor\n");

			if (all_philos_done_eating(data))
				return (arg);
			pthread_mutex_lock(&data->mutex);
			if (is_dead(&data->p[i]))
			{
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->mutex);
				return (arg);
			}
			pthread_mutex_unlock(&data->mutex);
			i++;
		}
		usleep(10);
	}
	return (arg);
}