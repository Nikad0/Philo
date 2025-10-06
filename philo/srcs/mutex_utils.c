/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:37:53 by erbuffet          #+#    #+#             */
/*   Updated: 2025/10/06 21:11:32 by erbuffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_count(t_philo *philo)
{
	print_philo_routine(philo->id, "is eating\n", philo->data);
	pthread_mutex_lock(&philo->e_mutex);
	philo->e_count++;
	pthread_mutex_unlock(&philo->e_mutex);
}

void	increment_finish(t_philo *philo)
{
	if (philo->e_count == philo->data->n_eat)
	{
		pthread_mutex_lock(&philo->data->finish_mutex);
		philo->data->finish++;
		pthread_mutex_unlock(&philo->data->finish_mutex);
	}
}

long long	elapsed_time_ms(struct timeval start)
{
	long long		t2_ms;
	long long		t1_ms;
	struct timeval	current;

	gettimeofday(&current, NULL);
	t1_ms = (start.tv_sec * 1000.0) + (start.tv_usec / 1000.0);
	t2_ms = (current.tv_sec * 1000.0) + (current.tv_usec / 1000.0);
	return (t2_ms - t1_ms);
}

void	sleep_ms(t_philo *philo, int time)
{
	long long	start;
	long long	target;
	int			elapsed_time;

	start = elapsed_time_ms(philo->start_time);
	target = start + time;
	while (elapsed_time_ms(philo->start_time) <= target)
	{
		if (is_dead(philo) && !check_death_flag(philo))
		{
			elapsed_time = elapsed_time_ms(philo->start_time);
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->death_flag = true;
			pthread_mutex_unlock(&philo->data->death_mutex);
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("%d %d died\n", elapsed_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return ;
		}
		if (check_death_flag(philo))
			return ;
		usleep(100);
	}
}

void	print_philo_routine(int philo_id, char *routine, t_data *data)
{
	long long	elapsed_time;

	elapsed_time = elapsed_time_ms(data->philo->start_time);
	if (!check_death_flag(data->philo))
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d %s", elapsed_time, philo_id, routine);
		pthread_mutex_unlock(&data->print_mutex);
	}
}
