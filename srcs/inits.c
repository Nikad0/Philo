/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:35:13 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/04 20:48:45 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].e_count = 0;
		data->philo[i].data = data;
		data->philo[i].fork_flag = true;
		gettimeofday(&data->philo[i].start_time, NULL);
		gettimeofday(&data->philo[i].last_meal, NULL);
		if (pthread_mutex_init(&data->philo[i].e_mutex, NULL))
			return (0);
		if (pthread_mutex_init(&data->philo[i].fork_mutex, NULL))
			return (0);
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (1);
}

int	init_thread_2(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->thread[i], NULL, start_routine,
				&data->philo[i]))
		{
			clean(data, i);
			return (0);
		}
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
	if (!init_mutex(data) || !init_philo(data) || !init_thread_2(data))
	{
		free(data->philo);
		free(data->thread);
		return (0);
	}
	return (1);
}

int	init(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!is_number(av[i]))
			return (0);
	}
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->n_eat = -1;
	data->death_flag = false;
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	if (init_thread(data) || data->n_philo <= 0 || data->t_die <= 0
		|| data->t_eat <= 0 || data->t_sleep <= 0)
	{
		clean(data, data->n_philo);
		return (0);
	}
	return (1);
}
