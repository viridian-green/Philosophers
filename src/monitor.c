/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/22 16:37:30 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *monitoring(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	while (1)
	{
		ft_usleep(1000);
		int i;
		i = 0;
		while (i < data->total_philo)
		{
			if (is_dead_or_done(data))
    		{
				printf("------------------------------------------->exit m loops");
            	return (NULL);
        	}
			pthread_mutex_lock(&data->dead_lock);
			if (is_dead(&data->p[i]))
			{
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->dead_lock);
			i++;
		}
		printf("------>done");
		// usleep(1000);
	}
	return (NULL);
}