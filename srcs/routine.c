/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:02:39 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/01 15:38:47 by erbuffet         ###   ########lyon.fr   */
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
	sleep_ms(philo, 5);
}

void	sleep_routine(t_philo *philo)
{
	print_philo_routine(philo->id, "is sleeping\n", philo->data);
	sleep_ms(philo, philo->data->t_sleep);
}

void	eat_routine(t_philo *philo)
{
	int	elapsed_time;

	print_philo_routine(philo->id, "is eating\n", philo->data);
	sleep_ms(philo, philo->data->t_eat);
	elapsed_time = elapsed_time_ms(philo->start_time);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_lock(philo->e_mutex);
	philo->e_count += 1;
	pthread_mutex_unlock(philo->e_mutex);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_philo_routine(philo->id, "is thinking\n", philo->data);
	if (philo->data->n_philo == 1)
		one_philo_check(philo);
	if (philo->id % 2 == 0)
		sleep_ms(philo, philo->data->t_sleep);
	while (philo->e_count != philo->data->n_eat && !check_death_flag(philo))
	{
		if (!check_death_flag(philo))
			attribute_fork(philo);
		if (!check_death_flag(philo))
			sleep_routine(philo);
		if (!check_death_flag(philo))
			think_routine(philo);
		else
			break ;
	}
	return (NULL);
}
