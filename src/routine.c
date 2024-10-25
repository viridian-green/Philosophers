/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:16 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/25 14:52:03 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	if (p->is_eating)
	{
		pthread_mutex_unlock(&p->data->mutex);
		return 0;
	}
	if (get_time() - p->last_meal >= p->data->time_die)
	{
		p->data->stop_simulation = 1;
		p->is_dead = 1;
		message("died", p);
		pthread_mutex_unlock(&p->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&p->data->mutex);
	return 0;
}

void lock_forks(t_philo *p)
{
	if (p->is_even)
	{
		pthread_mutex_lock(p->l_f);
		message("has taken a fork", p);
		pthread_mutex_lock(p->r_f);
		message("has taken a fork", p);
	} else
	{
		ft_usleep(10);
		pthread_mutex_lock(p->r_f);
		message("has taken a fork", p);
		pthread_mutex_lock(p->l_f);
		message("has taken a fork", p);
	}
}

void unlock_forks(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	p->is_eating = 0;
	if (p->is_even)
	{
		pthread_mutex_unlock(p->l_f);
		pthread_mutex_unlock(p->r_f);
	} else
	{
		pthread_mutex_unlock(p->r_f);
		pthread_mutex_unlock(p->l_f);
	}
	pthread_mutex_unlock(&p->data->mutex);
}
int is_eating(t_philo *p)
{
	lock_forks(p);
	message("is eating", p);
	pthread_mutex_lock(&p->data->mutex);
	p->last_meal = get_time();
	p->is_eating = 1;
	p->meals_eaten += 1;
	pthread_mutex_unlock(&p->data->mutex);
	ft_usleep(p->data->time_eat);
	unlock_forks(p);
	return 0;
}

int is_sleeping(t_philo *p)
{
	message("is sleeping", p);
	ft_usleep(p->data->time_sleep);
	return (0);
}
int is_thinking(t_philo *p)
{
	message("is thinking", p);
//    if (p->data->time_eat > p->data->time_die)
//        usleep(100);
//    else if (p->data->time_die - p->data->time_die - p->data->time_sleep < 0)
//        usleep(100);
//    else
//        usleep((p->data->time_die - p->data->time_eat - \
//            p->data->time_sleep) / 2 * 100);
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
		{
            sum_of_meals++;
        }
		pthread_mutex_unlock(&data->mutex);
		i++;
    }
	if (sum_of_meals == data->total_philo)
	{
		printf("---------------->done eating!");
 		return 1;
	}
	else
		return 0;
}

void *routine(void *arg)
{
	t_philo *p = (t_philo *)arg;
	p->data->start_time = get_time();
	int loop = 0;
	while (!is_dead(p))
	{
		pthread_mutex_lock(&p->data->mutex);
		if (p->data->stop_simulation)
		{
			pthread_mutex_unlock(&p->data->mutex);
			break;
		}
		pthread_mutex_unlock(&p->data->mutex);
		is_eating(p);
		pthread_mutex_lock(&p->data->mutex);
		if (p->data->stop_simulation)
		{
			pthread_mutex_unlock(&p->data->mutex);
			break;
		}
		pthread_mutex_unlock(&p->data->mutex);
		is_sleeping(p);
		pthread_mutex_lock(&p->data->mutex);
		if (p->data->stop_simulation)
		{
			pthread_mutex_unlock(&p->data->mutex);
			break;
		}
		pthread_mutex_unlock(&p->data->mutex);
		is_thinking(p);
	}
    return (NULL);
}

// void *routine(void *arg)
// {
// 	t_philo *p = (t_philo *)arg;
// 	p->data->start_time = get_time();
// 	int loop = 0;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&p->data->mutex);
// 		if (p->data->stop_simulation)
// 		{
// 			pthread_mutex_unlock(&p->data->mutex);
// 			break;
// 		}
// 	pthread_mutex_unlock(&p->data->mutex);
// 		is_eating(p);
// 		is_sleeping(p);
// 		is_thinking(p);
// 	}
// 	return (NULL);
// }


// void *routine(void *arg)
// {
// 	t_philo *p = (t_philo *)arg;
// 	p->data->start_time = get_time();
// 	int loop = 0;
// 	while (!p->data->stop_simulation)
// 	{
// 		is_eating(p);
// 		is_sleeping(p);
// 		is_thinking(p);
// 	}
// 	return (NULL);
// }