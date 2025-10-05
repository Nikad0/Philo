/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:35:13 by erbuffet          #+#    #+#             */
/*   Updated: 2025/10/06 00:58:37 by erbuffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].e_count = 0;
		data->philo[i].data = data;
		data->fork[i].flag = true;
		gettimeofday(&data->philo[i].start_time, NULL);
		gettimeofday(&data->philo[i].last_meal, NULL);
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].right_fork = &data->fork[(i + 1) % data->n_philo];
		if (pthread_mutex_init(&data->philo[i].e_mutex, NULL))
			return (0);
		if (pthread_mutex_init(&data->fork[i].mutex, NULL))
			return (0);
	}
	attribute_fork(data);
	return (1);
}

static int	init_thread_bis(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (0);
	if (pthread_mutex_init(&data->finish_mutex, NULL))
		return (0);
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

static int	init_thread(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (1);
	data->fork = malloc(sizeof(t_fork) * data->n_philo);
	if (!data->fork)
	{
		free(data->philo);
		return (1);
	}
	data->thread = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->thread)
	{
		free(data->philo);
		free(data->fork);
		return (1);
	}
	if (!init_philo(data) || !init_thread_bis(data))
	{
		free(data->philo);
		free(data->thread);
		free(data->fork);
		return (1);
	}
	return (0);
}

int	init(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (!is_number(av[i])
			|| ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
			return (0);
	data->n_philo = ft_atol(av[1]);
	data->t_die = ft_atol(av[2]);
	data->t_eat = ft_atol(av[3]);
	data->t_sleep = ft_atol(av[4]);
	data->n_eat = -1;
	data->death_flag = false;
	data->finish = 0;
	if (ac == 6)
		data->n_eat = ft_atol(av[5]);
	if (data->n_philo <= 0 || data->t_die <= 0 || data->n_philo >= 500
		|| data->t_eat <= 0 || data->t_sleep <= 0 || data->n_eat == 0)
		return (0);
	if (!init_thread(data))
	{
		clean(data, data->n_philo);
		return (1);
	}
	return (0);
}
