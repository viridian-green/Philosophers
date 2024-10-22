
#include "../philo.h"

// TODO : create a mutex for the start time
int threading_philos(t_data *data)
{
	int i = 0;
	pthread_t	monitor;
	while (i < data->total_philo)
	{
	if (pthread_create(&data->p[i].thread, NULL, routine, &data->p[i]))
	{
		return exit_error("Thread creation failed\n");
	}
	i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, monitoring, (void *)data);
 	while (i < data->total_philo)
	{
		pthread_join(data->p[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}

int parse_args(t_data *data, int argc, char **argv)
{
	// if (argc == 4)
	// {
	data->total_philo = 5;
	data->time_die = 800;
	data->time_eat = 200;
	data->time_sleep = 200;
	data->total_meals = 2;
	// data->total_philo = 1;
	// data->time_die = 800;
	// data->time_eat = 200;
	// data->time_sleep = 200;
	// 4 410 200 200
	return (0);
	// }
	// else
	// 	return (1);
}
void *monitoring(void *arg)
{
	t_data *data;
	data = (t_data *)arg;
	while (1)
	{
		ft_usleep(1000);
		printf("HELLO");
		int i;
		i = 0;
		while (i < data->total_philo)
		{
		if (is_dead_or_done(data))
        {
			printf("------------------------------------------->exit m loops");
            return (NULL);
        }
			pthread_mutex_lock(&data->dead_lock);
			if (is_dead(&data->p[i]))
			{
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->dead_lock);
			i++;
		}
		printf("------>done");
		// usleep(1000);
	}
	return (NULL);
}
int main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return exit_error("Error allocating memory for data\n");
	if (parse_args(data, argc, argv))
		return exit_error("Error. Invalid arguments\n");
	data_init(data, argv);
	threading_philos(data);
	destroy_mutex(data);
	free_all(data);
}