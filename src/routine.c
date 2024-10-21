/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:27:16 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/21 15:21:09 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//Double check if function is correct
int is_dead(t_philo *p)
{
	if (get_time() - p->last_meal > p->data->time_die)
	//&& !(p->is_eating))
	{
		p->is_dead = 1;
		message("has died", p);
		return (1);
	}
	return 0;
}

void lock_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->l_f);
		message("has taken a fork", p);
		pthread_mutex_lock(p->r_f);
		message("has taken a fork", p);
	} else
	{
		pthread_mutex_lock(p->r_f);
		message("has taken a fork", p);
		pthread_mutex_lock(p->l_f);
		message("has taken a fork", p);
	}
}
int is_eating(t_philo *p)
{
	lock_forks(p);
	if (p->meals_eaten == p->data->total_meals)
		return (1);
	message("is eating", p);
	pthread_mutex_lock(&p->data->meal_lock);
	p->last_meal = get_time();
	p->is_eating = 1;
	p->meals_eaten += 1;
	pthread_mutex_unlock(&p->data->meal_lock);
	p->is_eating = 0;
	ft_usleep(p->data->time_eat);
	pthread_mutex_unlock(p->r_f);
	pthread_mutex_unlock(p->l_f);
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

int is_dead_or_done(t_data *data)
{
    int i;

    // Lock mutex to check meal count safely
    pthread_mutex_lock(&data->meal_lock);
    i = 0;
	while (i++ < data->total_philo)
	{
        if (data->p[i].meals_eaten < data->total_meals) {
            pthread_mutex_unlock(&data->meal_lock);
            return 0;  // Not done eating
        }
    }
    pthread_mutex_unlock(&data->meal_lock);
    return 1;  // All philosophers are done eating
}



//Do I really need the is_dead
void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!is_dead(philo))
	{
		if (philo->id % 2 == 0)
			ft_usleep(1);
		if (is_dead_or_done(philo->data))  // Check again before eating
            return (NULL);
		is_eating(philo);
			// return NULL;
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

