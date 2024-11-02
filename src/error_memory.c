/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:15:47 by ademarti          #+#    #+#             */
/*   Updated: 2024/11/02 14:36:41 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	exit_error(char *error_message, t_data *data)
{
	ft_putstr_fd(error_message, 2);
	destroy_mutex(data);
	free_all(data);
	exit (1);
}

void	free_all(t_data *data)
{
	if (data->p)
		free(data->p);
	if (data->fork)
		free(data->fork);
	if (data)
		free(data);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->mutex);
}
