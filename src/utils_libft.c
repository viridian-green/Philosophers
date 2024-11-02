/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:41:57 by ademarti          #+#    #+#             */
/*   Updated: 2024/11/02 13:49:56 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


int	ft_atoi(const char *nptr, t_data *data)
{
	size_t	result;
	size_t	sign;
	size_t	i;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
		{
			exit_error("Error, arguments cannot be negative\n", data);
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9' )
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}