/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftumay < ftumay@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:12:59 by ftumay            #+#    #+#             */
/*   Updated: 2023/01/29 16:47:27 by ftumay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int ac, char **av)
{
	int	x;
	int	y;

	y = 1;
	if (!(ac == 6 || ac == 5))
		philo_error("Argument number is wrong");
	while (y < ac)
	{
		x = 0;
		while (av[y][x] != '\0')
		{
			if (av[y][0] == '+')
				x++;
			if (!(av[y][x] >= '0' && av[y][x] <= '9'))
				philo_error("Argument error");
			x++;
		}
		y++;
	}
}

void	a(int ac, char **av)
{
	t_data	data;

	check_args(ac, av);
	start_philo(ac, av, &data);
	end_philo(&data);
}

int	main(int ac, char **av)
{
	a(ac, av);
	system("leaks philo");
}
