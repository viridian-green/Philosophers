/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:12:29 by ademarti          #+#    #+#             */
/*   Updated: 2024/09/30 12:40:25 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


//Notice there is no time to think so thinking is essentially u_sleep/waiting
//for fork to be unlocked
typedef struct s_arg
{
	int				n_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
}	t_arg;


typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	pthread_mutex_t	r_f;
	pthread_mutex_t	l_f;
	t_arg			*arg;
	int 		flag;

}	t_philo;

