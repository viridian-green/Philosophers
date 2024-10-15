/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:40 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/15 15:04:30 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *monitor(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	while (1)
	{
		if (is_dead(data->p))
		{
			pthread_mutex_lock(&data->dead_lock);
		}
		pthread_mutex_unlock(&data->dead_lock);
		ft_usleep(100);
	}



}