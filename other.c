void monitor_philos(t_data *data)
{
	pthread_t	monitor;
	pthread_create(&monitor, NULL, monitoring, (void *)data);
	pthread_join(monitor, NULL);
}