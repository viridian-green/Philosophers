/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:12:29 by ademarti          #+#    #+#             */
/*   Updated: 2024/10/24 15:20:27 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	*l_f;
	int	meals_eaten;
	int is_even;
	int		is_dead;
	int		is_eating;
	long 	last_meal;
	long	has_eaten;
	t_data *data;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t *fork;
	pthread_mutex_t write_mutex;
	pthread_mutex_t	mutex;
	long		start_time;
	int				total_philo;
	int				total_meals;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				stop_simulation;
	t_philo			*p;
}	t_data;

//Initialize
int	init_philos(t_data *args);
int data_init(t_data *arg, char **argv);
int init_forks(t_data *args);

//Error/memory
int exit_error(char *error_message);
void destroy_mutex(t_data *data);
void free_all(t_data *data);

//Utils
int	ft_atoi(const char *nptr);
void	ft_usleep(long int time_in_ms);
long get_elapsed_time_microseconds(struct timeval start, struct timeval end);
void	ft_putstr_fd(char *s, int fd);
long	get_time(void);
void	message(char *str, t_philo *philo);

//Routine
int is_thinking(t_philo *p);
int is_sleeping(t_philo *p);
int is_eating(t_philo *p);
int is_dead(t_philo *p);
void *routine(void *arg);
int all_philos_done_eating(t_data *data);

//Monitoring
int check_death_each_philo(t_data *data);
int monitoring(t_data *data);

#endif