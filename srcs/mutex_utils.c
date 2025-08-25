/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 09:37:53 by erbuffet          #+#    #+#             */
/*   Updated: 2025/08/25 18:38:45 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, int fork_id)
{
	int	elapsed_time;

	pthread_mutex_lock(&philo->fork_mutex[fork_id]);
	while (philo->fork_bool[fork_id] == false)
		sleep_ms(philo, philo->data->t_eat);
	philo->fork_bool[fork_id] = false;
	elapsed_time = elapsed_time_ms(philo->start_time);
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
}

void	put_fork(t_philo *philo, int fork_id)
{
	philo->fork_bool[fork_id] = true;
	pthread_mutex_unlock(&philo->fork_mutex[fork_id]);
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
	while (elapsed_time_ms(philo->start_time) < target)
	{
		if (is_dead(philo) && !philo->data->death_flag)
		{
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->death_flag = true;
			pthread_mutex_unlock(&philo->data->death_mutex);
			pthread_mutex_lock(&philo->data->print_mutex);
			elapsed_time = elapsed_time_ms(philo->start_time);
			printf("%d %d died\n", elapsed_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return ;
		}
		if (philo->data->death_flag)
			return ;
		usleep(500);
	}
}

void	print_philo_routine(int philo_id, char *routine, t_data *data)
{
	long long	elapsed_time;

	pthread_mutex_lock(&data->print_mutex);
	pthread_mutex_lock(&data->death_mutex);
	elapsed_time = elapsed_time_ms(data->philo->start_time);
	if (!data->death_flag)
		printf("%lld %d %s", elapsed_time, philo_id, routine);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}
