/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <adelemartin@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:12:29 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/04 12:39:40 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

//Notice there is no time to think so thinking is essentially u_sleep/waiting
//for fork to be unlocked

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	*l_f;
	int		is_dead;
	long	start_time;
	long 	last_meal;
	long	has_eaten;

}	t_philo;

typedef struct s_data
{
	pthread_mutex_t *fork;
	pthread_mutex_t write_mutex;
	int				total_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	t_philo			*p;
}	t_data;


//Initialize
int	init_philos(t_data *args);
int data_init(t_data *arg, char **argv);
int init_forks(t_data *args);

//Error/memory
int exit_error(char *error_message);

//Utils
int	ft_atoi(const char *nptr);
void	ft_usleep(long int time_in_ms);
long get_elapsed_time_microseconds(struct timeval start, struct timeval end);
void	ft_putstr_fd(char *s, int fd);
long int	get_time(void);
void	message(char *str, t_philo *philo);

#endif