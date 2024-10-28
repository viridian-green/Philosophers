/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/28 15:25:58 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int check_simulation(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	if (p->data->stop_simulation || p->is_dead)
	{
		pthread_mutex_unlock(&p->data->mutex);
		return 1;
	}
	pthread_mutex_unlock(&p->data->mutex);
	return (0);
}

int all_philos_done_eating(t_data *data)
{
    int i;
	int sum_of_meals = 0;
    i = 0;

	while (i < data->total_philo)
	{
		pthread_mutex_lock(&data->mutex);
        if (data->p[i].meals_eaten == data->total_meals)
            sum_of_meals++;
		pthread_mutex_unlock(&data->mutex);
		i++;
    }
	if (sum_of_meals == data->total_philo)
	{
		// printf("---------------->done eating!");
 		return 1;
	}
	else
		return 0;
}


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