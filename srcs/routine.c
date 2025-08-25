/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:02:39 by erbuffet          #+#    #+#             */
/*   Updated: 2025/08/25 18:39:54 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_check(t_philo *philo)
{
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	sleep_ms(philo, philo->data->t_eat);
}

void	think_routine(t_philo *philo)
{
	if (philo->e_count == philo->data->n_eat)
		return ;
	print_philo_routine(philo->id, "is thinking\n", philo->data);
}

void	sleep_routine(t_philo *philo)
{
	print_philo_routine(philo->id, "is sleeping\n", philo->data);
	sleep_ms(philo, philo->data->t_sleep);
}

void	eat_routine(t_philo *philo)
{
	int	left;
	int	right;
	int	elapsed_time;

	left = philo->id - 1;
	right = (philo->id) % philo->data->n_philo;
	if (philo->id % 2 == 0)
	{
		take_fork(philo, left);
		take_fork(philo, right);
	}
	if (philo->id % 2 != 0)
	{
		take_fork(philo, right);
		take_fork(philo, left);
	}
	elapsed_time = elapsed_time_ms(philo->start_time);
	gettimeofday(&philo->last_meal, NULL);
	print_philo_routine(philo->id, "is eating\n", philo->data);
	sleep_ms(philo, philo->data->t_eat);
	pthread_mutex_lock(philo->e_mutex);
	philo->e_count += 1;
	pthread_mutex_unlock(philo->e_mutex);
	put_fork(philo, left);
	put_fork(philo, right);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philo == 1)
		one_philo_check(philo);
	if (philo->id % 2 != 0)
	{
		think_routine(philo);
		sleep_ms(philo, philo->data->t_sleep);
	}
	while (philo->e_count != philo->data->n_eat && !philo->data->death_flag)
	{
		if (!philo->data->death_flag)
			eat_routine(philo);
		if (!philo->data->death_flag)
			sleep_routine(philo);
		if (!philo->data->death_flag)
			think_routine(philo);
		else
			break ;
	}
	return (NULL);
}
