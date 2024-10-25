/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:19:23 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/25 15:21:30 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!philo->is_dead)
	{
		printf("%ld %d %s\n",
		get_time() - philo->data->start_time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//add is dead check here
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
