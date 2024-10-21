/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/21 15:46:51 by ademarti         ###   ########.fr       */
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
				break;
			}
			pthread_mutex_unlock(&data->dead_lock);
			i++;
		}
		if (data->stop_simulation)
			break;
		usleep(1000);  // Avoid busy-waiting
	}
	return (NULL);
}