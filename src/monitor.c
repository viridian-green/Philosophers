/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/16 13:41:33 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_death_each_philo(t_data *data)
{
	int i = 0;
	while (i < data->total_philo)
	{
		if (is_dead(&data->p[i]))
			return (1);
		i++;
	}
	return 0;
}

void *monitoring(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (check_death_each_philo(data))
		{
			data->stop_simulation = 1;
			break;
		}
		pthread_mutex_unlock(&data->dead_lock);
		if (data->stop_simulation)
		{
            break; // Exit monitoring loop
        }
		ft_usleep(100);
	}
	return (NULL);
}