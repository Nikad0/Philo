/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikado <nikado@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:10:29 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/05 11:23:54 by nikado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_data *data)
{
	int i = -1;
	if (!data || !data->philo)
		return ;
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->fork[i].mutex);
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
	if (data->thread)
		free(data->thread);
	if (data->philo)
		free(data->philo);
	if (data->fork)			
		free(data->fork);
}
