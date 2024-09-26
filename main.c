/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:14:51 by ademarti          #+#    #+#             */
/*   Updated: 2024/09/26 15:08:45 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *eat(void *data)
{
	printf("I am eating");
	sleep(3);
	printf("I am done");
	return NULL;
}

int main()
{
	pthread_t philo_1;
	pthread_t philo_2;
	pthread_create(&philo_1, NULL, eat, NULL); //creare a thread with pthread
	pthread_create(&philo_2, NULL, eat, NULL); //creare a thread with pthread

	//Tzo threads are running simalteneously

	pthread_join();

}