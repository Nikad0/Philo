/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:35:13 by erbuffet          #+#    #+#             */
/*   Updated: 2025/08/24 00:05:48 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex_2(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo->fork_bool[i] = true;
		data->philo[i].fork_bool = data->philo->fork_bool;
		data->philo[i].fork_mutex = data->philo->fork_mutex;
		data->philo[i].e_mutex = data->philo->e_mutex;
		pthread_mutex_init(&data->philo->fork_mutex[i], NULL);
		pthread_mutex_init(&data->philo->e_mutex[i], NULL);
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	data->philo->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->philo->fork_mutex)
		return (0);
	data->philo->e_mutex = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->philo->e_mutex)
	{
		free(data->philo->fork_mutex);
		return (0);
	}
	data->philo->fork_bool = malloc(sizeof(bool) * data->n_philo);
	if (!data->philo->fork_bool)
	{
		free(data->philo->fork_mutex);
		free(data->philo->e_mutex);
		return (0);
	}
	if (!init_mutex_2(data))
		return (0);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (1);
}

int	init_thread_2(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = j;
		data->philo[i].e_count = 0;
		data->philo[i].data = data;
		gettimeofday(&data->philo[i].start_time, NULL);
		gettimeofday(&data->philo[i].last_meal, NULL);
		if (pthread_create(&data->thread[i], NULL, start_routine,
				&data->philo[i]))
			clean(data, i);
		j++;
	}
	return (1);
}

int	init_thread(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (0);
	data->thread = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->thread)
	{
		free(data->philo);
		return (0);
	}
	if (!init_mutex(data))
	{
		free(data->philo);
		free(data->thread);
		return (0);
	}
	if (!init_thread_2(data))
		return (0);
	return (1);
}

int	init_philo(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_number(av[i]))
		{
			printf("error: arg is not a number\n");
			return (0);
		}
	}
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->n_eat = -1;
	data->death_flag = false;
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	if (init_thread(data))
	{
		clean(data, data->n_philo);
		return (0);
	}
	return (1);
}
