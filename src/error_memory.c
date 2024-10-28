/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:15:47 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/28 15:13:55 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int exit_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	// free_all(d)
	exit (1);
}

void free_all(t_data *data)
{
	if (data->p)
		free(data->p);
	if (data->fork)
		free(data->fork);
	if (data)
		free(data);
}

void destroy_mutex(t_data *data)
{
	int i = 0;
	while (i < data->total_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->mutex);
}