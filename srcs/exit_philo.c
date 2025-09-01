/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:10:29 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/01 13:54:06 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_data *data)
{
	int	i;

	if (!data || !data->philo)
		return ;
	i = -1;
	while (++i < data->n_philo)
	{
		if (data->philo->fork_mutex)
			pthread_mutex_destroy(&data->philo->fork_mutex[i]);
		if (data->philo->e_mutex)
			pthread_mutex_destroy(&data->philo->e_mutex[i]);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

void	clean_philo(t_philo *philo)
{
	if (philo)
	{
		if (philo->fork_mutex)
			free(philo->fork_mutex);
		if (philo->e_mutex)
			free(philo->e_mutex);
		if (philo->fork_bool)
			free(philo->fork_bool);
		free(philo);
	}
	return ;
}

void	clean(t_data *data, int index)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	if (data->thread)
		while (++i < index)
			pthread_join(data->thread[i], NULL);
	destroy(data);
	clean_philo(data->philo);
	if (data->thread)
		free(data->thread);
}
