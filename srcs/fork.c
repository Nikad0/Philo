/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:09:04 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/02 15:40:43 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	attribute_fork(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = (philo->id) % philo->data->n_philo;
	if (philo->id % 2 == 0)
	{
		take_fork(philo, left, right);
		if (!check_fork_flag(philo, left) && !check_fork_flag(philo, right))
			eat_routine(philo);
		put_fork(philo, left, right);
	}
	else
	{
		take_fork(philo, right, left);
		if (!check_fork_flag(philo, left) && !check_fork_flag(philo, right))
			eat_routine(philo);
		put_fork(philo, left, right);
	}
}

void	take_fork(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->fork_mutex[left]);
	philo->fork_bool[left] = false;
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	pthread_mutex_unlock(&philo->fork_mutex[left]);
	pthread_mutex_lock(&philo->fork_mutex[right]);
	philo->fork_bool[right] = false;
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	pthread_mutex_unlock(&philo->fork_mutex[right]);
}

void	put_fork(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->fork_mutex[left]);
	philo->fork_bool[left] = true;
	pthread_mutex_unlock(&philo->fork_mutex[left]);
	pthread_mutex_lock(&philo->fork_mutex[right]);
	philo->fork_bool[right] = true;
	pthread_mutex_unlock(&philo->fork_mutex[right]);
}
