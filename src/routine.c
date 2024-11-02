/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:16 by ademarti          #+#    #+#             */
/*   Updated: 2024/11/02 14:31:13 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_dies(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	if ((get_time() - p->last_meal >= p->data->time_die))
	{
		p->is_dead = 1;
		death_message(p);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&p->data->mutex);
	return (0);
}


void unlock_forks(t_philo *p)
{
		pthread_mutex_unlock(p->r_f);
		pthread_mutex_unlock(p->l_f);

}

//TODO : chqnge the ft_usleep around
int lock_forks(t_philo *p)
{
	if (p->is_even)
		pthread_mutex_lock(p->l_f);
	else
	{
		pthread_mutex_lock(p->r_f);
	}
	pthread_mutex_lock(&p->data->mutex);
	message("has taken a fork", p);
	pthread_mutex_unlock(&p->data->mutex);
	if (p->data->total_philo == 1)
	{
		ft_usleep(p->data->time_die);
		pthread_mutex_unlock(p->r_f);
		return (1);
	}
	if (p->is_even)
		pthread_mutex_lock(p->r_f);
	else
		pthread_mutex_lock(p->l_f);
	pthread_mutex_lock(&p->data->mutex);
	message("has taken a fork", p);
	pthread_mutex_unlock(&p->data->mutex);
	return (0);
}

int	is_eating(t_philo *p)
{
	if (lock_forks(p) == 1)
		return 1;
	pthread_mutex_lock(&p->data->mutex);
	message("is eating", p);
	p->last_meal = get_time();
	p->meals_eaten += 1;
	pthread_mutex_unlock(&p->data->mutex);
	ft_usleep(p->data->time_eat);
	unlock_forks(p);
	return 0;
}

int is_sleeping(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	message("is sleeping", p);
	pthread_mutex_unlock(&p->data->mutex);
	ft_usleep(p->data->time_sleep);
	return (0);
}

int is_thinking(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	message("is thinking", p);
	pthread_mutex_unlock(&p->data->mutex);
	if ((p->data->total_philo % 2 == 0))
		usleep(10);
    if (p->data->time_die - p->data->time_eat - p->data->time_sleep <= 0)
		usleep(900);
   else
		usleep((p->data->time_die - p->data->time_eat - \
		p->data->time_sleep) * 900);
	return (0);
}

//TODO: Check time to die for one philo routine
void *routine(void *arg)
{
	t_philo *p = (t_philo *)arg;
	int loop = 0;
	// if (p->id == 1 && (p->data->total_philo % 2) != 0 \
	// 		&& p->meals_eaten == 0)
	// 		usleep(p->data->time_eat * 1000);
	if (p->is_even)
		ft_usleep(1);
	while (1)
	{
		is_eating(p);
		if (check_simulation(p))
			break;
		is_sleeping(p);
		is_thinking(p);
	}
	return (NULL);
}