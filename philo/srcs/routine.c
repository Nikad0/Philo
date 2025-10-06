/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:02:39 by erbuffet          #+#    #+#             */
/*   Updated: 2025/10/06 18:20:13 by erbuffet         ###   ########.fr       */
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
	if (check_death_flag(philo))
		return ;
	print_philo_routine(philo->id, "is thinking\n", philo->data);
	sleep_ms(philo, 2);
}

void	sleep_routine(t_philo *philo)
{
	if (check_death_flag(philo))
		return ;
	print_philo_routine(philo->id, "is sleeping\n", philo->data);
	sleep_ms(philo, philo->data->t_sleep);
}

void	eat_routine(t_philo *philo)
{
	if (check_death_flag(philo))
		return ;
	if (two_fork_taken(philo, philo->left_fork, philo->right_fork))
	{
		philo_eat_count(philo);
		sleep_ms(philo, philo->data->t_eat);
		gettimeofday(&philo->last_meal, NULL);
		put_fork(philo->right_fork);
		put_fork(philo->left_fork);
		increment_finish(philo);
		return ;
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
	while (!check_death_flag(philo))
	{
		eat_routine(philo);
		if (meal_monitoring(philo))
			return (NULL);
		sleep_routine(philo);
		if (meal_monitoring(philo))
			return (NULL);
		think_routine(philo);
		if (meal_monitoring(philo))
			return (NULL);
	}
	return (NULL);
}
