/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/09/26 19:47:26 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <header.h>

void *eat(void *data)
{
	fprintf(stderr, "I am eating");
	usleep(100000);
	fprintf(stderr, "I am done");
	pthread_exit(NULL);
}

void *sleeping(void *data)
{
	fprintf(stderr, "I am sleeping");
	usleep(100000);
	fprintf(stderr, "zzzz");
	pthread_exit(NULL);
}

int main()
{
	//to retrieve thread id
	//pthread_self();

	//Each thread has an ID number
	pthread_t philo_1;
	//pthread_t eating_routine;
	pthread_t philo_2;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	//Creating the eating routine with the pthread function
	if (pthread_create(&philo_1, NULL, eat, NULL))
		return (EXIT_FAILURE);
	if (pthread_create(&philo_2, NULL, sleeping, NULL)) //creare a thread with pthread
		return (EXIT_FAILURE);

	//Just like parent waiting for its child with wait() function
	//The main waits for threads before exiting
	pthread_join(philo_1, NULL);
	pthread_join(philo_2, NULL);
	pthread_mutex_destroy(&mutex);
}