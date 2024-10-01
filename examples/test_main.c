/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/01 14:48:15 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *eat(void *data)
{
	printf("I am eating");
	usleep(100000);
	printf("I am done");
	return (NULL);
}

void *sleeping(void *data)
{
	printf("I am sleeping");
	usleep(100000);
	printf("zzzz");
	return (NULL);
}

void data_init(t_data *arg, t_philo philo, char **argv)
{
	//arg->n_philo = argv[0];
	arg->n_philo = 2;
	arg->time_die = argv[1];
	arg->time_eat = argv[2];
	arg->time_sleep = argv[3];

}

int main(int argc, char **argv)
{
	t_data *arg;
	t_philo philo_1;
	t_philo philo_2;
	pthread_mutex_t fork = PTHREAD_MUTEX_INITIALIZER;

	data_init(arg, argv);



	if (pthread_create(&philo_1.thread, NULL, eat, NULL))
		return ;
	if (pthread_create(&philo_2.thread, NULL, sleeping, NULL))
		return ;

	pthread_join(philo_1.thread, NULL);
	pthread_join(philo_2.thread, NULL);
	pthread_mutex_destroy(&fork);
	sleep(6);
}