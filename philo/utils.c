/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftumay < ftumay@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:07:31 by ftumay            #+#    #+#             */
/*   Updated: 2023/01/29 17:48:51 by ftumay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_error(char *str)
{
	printf("%s\n", str);
}

unsigned long	get_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_philo philo, char *str)
{
	long	current_time;

	current_time = get_time() - philo.data->start_time;
	if (philo.data->is_alive == true)
		printf("%ld %d %s\n", current_time, philo.philo_id, str);
	pthread_mutex_unlock(&philo.data->print_lock);
}

void	end_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		i++;
	}
	free(data->fork_lock);
	free(data->philo);
}

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
		num = (num * 10) + (str[i++] - '0');
	return (num);
}
