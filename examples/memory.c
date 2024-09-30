#include "header.h"

void exit_on_error(t_data *data)
{
	free (data);
	exit(1);
}

void free_data(t_mutex mut)
{
	pthread_mutex_destroy(mut.mutex);
	free(mut.mutex);
}