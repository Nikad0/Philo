/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:10:29 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/04 21:33:30 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_data *data)
{
	if (!data || !data->philo)
		return ;
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	for (int i = 0; i < data->n_philo; i++)
		pthread_mutex_destroy(&data->philo[i].fork_mutex);
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
}
