/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:16 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/23 16:51:03 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//Double check if function is correct
int is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->data->mutex);
	if (get_time() - p->last_meal > p->data->time_die && !(p->is_eating))
	{
		p->is_dead = 1;
		message("has died", p);
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
int is_eating(t_philo *p)
{
	lock_forks(p);
	// if (p->meals_eaten == p->data->total_meals)
	// 	return (1);
	message("is eating", p);
	pthread_mutex_lock(&p->data->mutex);
	p->last_meal = get_time();
	p->is_eating = 1;
	p->meals_eaten += 1;
	pthread_mutex_unlock(&p->data->mutex);
	ft_usleep(p->data->time_eat);
	p->is_eating = 0;
	if (p->is_even)
	{
		pthread_mutex_unlock(p->l_f);
		pthread_mutex_unlock(p->r_f);
	}
	else
	{
		pthread_mutex_unlock(p->r_f);
		pthread_mutex_unlock(p->l_f);
	}
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
	return (0);
}

int all_philos_done_eating(t_data *data)
{
    int i;
	int sum_of_meals = 0;

    pthread_mutex_lock(&data->mutex);
    i = 0;
	while (i < data->total_philo)
	{
		printf("enter loop\n");
        if (data->p[i].meals_eaten == data->total_meals)
		{
            sum_of_meals++;
        }
		i++;
    }
	printf("--->%d", sum_of_meals);
	printf("leave loop\n");
    pthread_mutex_unlock(&data->mutex);
	if (sum_of_meals == data->total_philo)
	{
		printf("---------------->done eating!");
 		return 1;
	}
	else
		return 0;
}

//Do I really need the is_dead
void *routine(void *arg)
{
	t_philo *p = (t_philo *)arg;
	p->data->start_time = get_time();
	int loop = 0;
	while (1)
	{
		printf("loops%d\n", loop++);
		is_eating(p);
		is_sleeping(p);
		is_thinking(p);
	}
	return (NULL);
}

