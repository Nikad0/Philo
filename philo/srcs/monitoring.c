/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:02:39 by erbuffet          #+#    #+#             */
/*   Updated: 2025/10/06 01:27:14 by erbuffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_monitoring(t_philo *philo)
{
	if (philo)
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (philo->data->finish == philo->data->n_philo)
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	return (0);
}

bool	check_death_flag(t_philo *philo)
{
	bool	is_dead_flag;

	pthread_mutex_lock(&philo->data->death_mutex);
	is_dead_flag = philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (is_dead_flag);
}

bool	is_dead(t_philo *philo)
{
	struct timeval	current;
	long long		t2_ms;
	long long		t1_ms;

	if (philo->data->n_philo == 1)
		return (true);
	gettimeofday(&current, NULL);
	t1_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	t2_ms = (philo->last_meal.tv_sec * 1000) + (philo->last_meal.tv_usec
			/ 1000);
	if ((t1_ms - t2_ms) >= philo->data->t_die)
		return (true);
	else
		return (false);
}
