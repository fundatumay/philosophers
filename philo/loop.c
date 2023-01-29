/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftumay < ftumay@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:13:25 by ftumay            #+#    #+#             */
/*   Updated: 2023/01/29 15:22:23 by ftumay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_must_eat(t_data *data)
{
	int	i;

	i = 0;
	if (data->must_eat > 0)
	{
		while (i < data->num_philo)
		{
			if (data->philo[i].eat_count >= data->must_eat)
				data->a_philo_finished_eating++;
			i++;
		}
		if (data->a_philo_finished_eating >= data->num_philo)
		{
			data->is_alive = false;
			return (1);
		}
	}
	return (0);
}

void	eat_func(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_lock[philo->left_fork]);
	print(*philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork_lock[philo->right_fork]);
	print(*philo, "has taken a fork");
	print(*philo, "is eating");
	usleep(philo->data->t_eat * 1000);
	philo->last_eat = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->fork_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork_lock[philo->right_fork]);
}

void	*main_loop(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->philo_id % 2 != 0)
	{
		print(*philo, "is_thinking");
		usleep(philo->data->t_eat * 1000);
	}
	while (philo->data->is_alive == true)
	{
		eat_func(philo);
		print(*philo, "is sleeping");
		usleep(philo->data->t_sleep * 1000);
		print(*philo, "is thinking");
	}
	print(*philo, "dead");
	return (NULL);
}

void	*check_loop(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (check_must_eat(data) == 0)
	{
		i = 0;
		while (i < data->num_philo)
		{
			if ((get_time() - data->philo[i].last_eat) > data->t_die)
			{
				print(data->philo[i], "dead");
				data->is_alive = false;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
