/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftumay < ftumay@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:08:19 by ftumay            #+#    #+#             */
/*   Updated: 2023/01/29 15:02:52 by ftumay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_up_args(int ac, char **av, t_data *data)
{
	data->must_eat = 0;
	data->num_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	if (data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0
		|| data->num_philo <= 1 || data->num_philo > 200)
		philo_error("Check arguments");
	data->start_time = get_time();
	data->a_philo_finished_eating = 0;
	data->is_alive = true;
}

void	set_up_philos(t_data *data)
{
	int	i;

	data->philo = (t_philo *) malloc(sizeof(t_philo) * data->num_philo);
	data->fork_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			* data->num_philo);
	if (!data->philo || !data->fork_lock)
		philo_error("Allocation failed");
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].philo_id = i + 1;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->num_philo;
		data->philo[i].eat_count = 0;
		data->philo[i].last_eat = get_time();
		data->philo[i].data = data;
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
}

void	set_up_threads(t_data *data)
{
	int			i;
	pthread_t	watcher_id;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL, &main_loop,
				&data->philo[i]) == -1)
		{
			philo_error("pthread_create Error");
		}
		i++;
	}
	if (pthread_create(&watcher_id, NULL, &check_loop, data) == -1)
		philo_error("pthread_create error");
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
}

void	start_philo(int ac, char **av, t_data *data)
{
	set_up_args(ac, av, data);
	set_up_philos(data);
	set_up_threads(data);
}
