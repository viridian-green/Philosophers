/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:12:29 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/02 13:54:53 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

//Notice there is no time to think so thinking is essentially u_sleep/waiting
//for fork to be unlocked
typedef struct s_data
{
	pthread_mutex_t *fork;
	int				total_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	*l_f;
	int 		flag;

}	t_philo;

//Initialize
void	init_philos(t_philo *philos, t_data *args);
void data_init(t_data *arg, t_philo *philos, char **argv);
void init_forks(t_philo *philos, t_data *args);

//Error/memory
int exit_error(char *error_message);

//Utils
int	ft_atoi(const char *nptr);
void precise_usleep(long usec);
long get_elapsed_time_microseconds(struct timeval start, struct timeval end);
void	ft_putstr_fd(char *s, int fd);

#endif