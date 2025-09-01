/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:09:04 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/01 10:31:56 by erbuffet         ###   ########lyon.fr   */
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
		take_fork(philo, left, right);
	else if (philo->id % 2 != 0)
		take_fork(philo, right, left);
}

void	take_fork(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->fork_mutex[left]);
	pthread_mutex_lock(&philo->fork_mutex[right]);
	philo->fork_bool[left] = false;
	philo->fork_bool[right] = false;
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	if (!philo->fork_bool[left] && !philo->fork_bool[right])
		eat_routine(philo);
	put_fork(philo, left, right);
}

void	put_fork(t_philo *philo, int left, int right)
{
	philo->fork_bool[left] = true;
	philo->fork_bool[right] = true;
	pthread_mutex_unlock(&philo->fork_mutex[left]);
	pthread_mutex_unlock(&philo->fork_mutex[right]);
}
