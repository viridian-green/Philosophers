/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/25 15:32:21 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


// int monitoring(t_data *data)
// 	usleep(100);
// 	while (!data->stop_simulation)
// 	{
// 		int i;
// 		i = 0;
// 		while (i < data->total_philo)
// 		{
// 			pthread_mutex_lock(&data->mutex);
// 			if (is_dead(data->p) || all_philos_done_eating(data))
// 			{
// 				data->stop_simulation = 1;
// 				pthread_mutex_lock(&data->mutex);
// 				break;
// 			}
// 			pthread_mutex_unlock(&data->mutex);
// 			i++;
// 		}
// 		usleep(10);
// 	}
// 	return 1;
// }

//protect the flags here
int monitoring(t_data *data)
{
	usleep(100);

	int done = 0;
	while (1)
	{
		int i;
		i = 0;
		while (i < data->total_philo)
		{
			if (is_dead(data->p) || all_philos_done_eating(data))
			{

				pthread_mutex_lock(&data->mutex);
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->mutex);
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