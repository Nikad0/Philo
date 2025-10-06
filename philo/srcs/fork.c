/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:09:04 by erbuffet          #+#    #+#             */
/*   Updated: 2025/10/06 21:17:32 by erbuffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	two_fork_taken(t_philo *philo, t_fork *left_fork, t_fork *right_fork)
{
	while (1)
	{
		if (take_fork(left_fork))
		{
			print_philo_routine(philo->id, "has taken a fork\n", philo->data);
			while (1)
			{
				if (take_fork(right_fork))
				{
					print_philo_routine(philo->id,
						"has taken a fork\n", philo->data);
					return (1);
				}
			}
		}
		usleep(100);
	}
	return (0);
}

bool	take_fork(t_fork *fork)
{
	bool	success;

	success = 0;
	pthread_mutex_lock(&fork->mutex);
	if (fork->flag == true)
	{
		fork->flag = false;
		success = 1;
	}
	pthread_mutex_unlock(&fork->mutex);
	return (success);
}

void	put_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->flag = true;
	pthread_mutex_unlock(&fork->mutex);
}

void	attribute_fork(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (i % 2 == 0)
		{
			data->philo[i].left_fork = &data->fork[i];
			data->philo[i].right_fork = &data->fork[(i + 1) % data->n_philo];
		}
		else
		{
			data->philo[i].left_fork = &data->fork[(i + 1) % data->n_philo];
			data->philo[i].right_fork = &data->fork[i];
		}
	}
}
