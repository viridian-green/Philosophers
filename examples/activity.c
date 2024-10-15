/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:58:15 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/15 13:40:55 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	write_status(char *str, t_philo *ph)
// {
// 	long int		time;

// 	time = -1;
// 	time = actual_time() - ph->pa->start_t;
// 	if (time >= 0 && time <= 2147483647 && !check_death(ph, 0))
// 	{
// 		printf("%ld ", time);
// 		printf("Philo %d %s", ph->id, str);
// 	}
// }

void	message(char *str, t_philo *philo, t_data *data)
{
	if (philo->is_dead == 0)
		printf("%ld %d %s\n", get_time() - philo->start_time, \
		philo->id, str);
}