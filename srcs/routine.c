/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:02:39 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/06 13:29:02 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo_check(t_philo *philo)
{
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	usleep(1000 * philo->data->t_die);
	printf("%d %d died\n", philo->data->t_die, philo->id);
}

void	think_routine(t_philo *philo)
{
	if (philo->e_count == philo->data->n_eat)
		return ;
	print_philo_routine(philo->id, "is thinking\n", philo->data);
	sleep_ms(philo, 2 * philo->data->t_eat - philo->data->t_sleep);
}

void	sleep_routine(t_philo *philo)
{
	print_philo_routine(philo->id, "is sleeping\n", philo->data);
	sleep_ms(philo, philo->data->t_sleep);
}

void	eat_routine(t_philo *philo)
{
	while (1)
	{
		if (take_fork(philo->left_fork))
		{
			if (take_fork(philo->right_fork))
			{
				gettimeofday(&philo->last_meal, NULL);
				print_philo_routine(philo->id, "is eating\n", philo->data);
				sleep_ms(philo, philo->data->t_eat);
				pthread_mutex_lock(&philo->e_mutex);
				philo->e_count++;
				pthread_mutex_unlock(&philo->e_mutex);
				put_fork(philo->right_fork);
				put_fork(philo->left_fork);
				return ;
			}
			put_fork(philo->left_fork);
		}
		sleep_ms(philo, 1);
	}
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_philo_routine(philo->id, "is thinking\n", philo->data);
	if (philo->data->n_philo == 1)
	{
		one_philo_check(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		sleep_ms(philo, philo->data->t_sleep);
	while (philo->e_count != philo->data->n_eat && !check_death_flag(philo))
	{
		if (!check_death_flag(philo))
			eat_routine(philo);
		if (!check_death_flag(philo))
			sleep_routine(philo);
		if (!check_death_flag(philo))
			think_routine(philo);
		else
			break ;
	}
	return (NULL);
}
