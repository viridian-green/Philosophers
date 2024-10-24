/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/24 13:54:28 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int monitoring(t_data *data)
{
	int done = 0;
	usleep(100);
	while (1)
	{
		int i;
		i = 0;
		while (i < data->total_philo)
		{
			if (all_philos_done_eating(data))
			{
				printf("----------------->YES");
				data->stop_simulation = 1;
				done = 1;
				break;
			}
			i++;
		}
		if (done)
			break;
		usleep(10);
	}
	return 1;
}


// void *monitoring(void *arg)
// {
// 	t_data *data;
// 	usleep(1000);
// 	data = (t_data *)arg;
// 	while (1)
// 	{ // Avoid busy-waiting
// 		int i;
// 		i = 0;
// 		while (i < data->total_philo)
// 		{
// 			printf("looping monitor\n");

// 			if (all_philos_done_eating(data))
// 				return (arg);
// 			pthread_mutex_lock(&data->mutex);
// 			if (is_dead(&data->p[i]))
// 			{
// 				data->stop_simulation = 1;
// 				pthread_mutex_unlock(&data->mutex);
// 				return (arg);
// 			}
// 			pthread_mutex_unlock(&data->mutex);
// 			i++;
// 		}
// 		usleep(10);
// 	}
// 	return (arg);
// }