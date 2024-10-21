/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/21 16:12:31 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *monitoring(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	while (1)
	{
		int i;
		i = 0;
		while (i < data->total_philo)
		{
			pthread_mutex_lock(&data->dead_lock);
			if (is_dead(&data->p[i]))
			{
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (arg);
			}
			pthread_mutex_unlock(&data->dead_lock);
			i++;
		}
		usleep(1000);  // Avoid busy-waiting
	}
	return (arg);
}