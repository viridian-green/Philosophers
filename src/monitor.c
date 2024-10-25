/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/25 13:14:18 by ademarti         ###   ########.fr       */
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

int monitoring(t_data *data)
{
	usleep(100);
	while (!data->stop_simulation)
	{
		int i;
		i = 0;
		while (i < data->total_philo)
		{
			if (is_dead(data->p) || all_philos_done_eating(data))
			{
				message("died", data->p);
				data->stop_simulation = 1;
				break;
			}
			i++;
		}
		usleep(10);
	}
	return 1;
}