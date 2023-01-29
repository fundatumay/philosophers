/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftumay < ftumay@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:12:04 by ftumay            #+#    #+#             */
/*   Updated: 2023/01/29 15:26:06 by ftumay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pthread_t iş parçacığını tanımlamak için kullanılır. pthread_create fonk.
// tarafından döndürülen değer bunda saklanır ve pthread_join gibi fonk. kul.

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data		*data;
	int			philo_id;
	int			right_fork;
	int			left_fork;
	int			eat_count;
	long		last_eat;
	pthread_t	thread_id;
}		t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				num_philo;
	int				must_eat;
	int				a_philo_finished_eating;
	unsigned long	t_die;
	int				t_eat;
	int				t_sleep;
	unsigned long	start_time;
	bool			is_alive;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	print_lock;
}		t_data;

void			start_philo(int ac, char **av, t_data *data);
void			set_up_args(int ac, char **av, t_data *data);
void			set_up_philos(t_data *data);
void			set_up_threads(t_data *data);
void			*main_loop(void *args);
void			*check_loop(void *args);
int				check_must_eat(t_data *data);
void			print(t_philo philo, char *str);
void			eat_func(t_philo *philo);
void			philo_error(char *str);
unsigned long	get_time(void);
int				ft_atoi(char *str);
void			end_philo(t_data *data);

#endif
